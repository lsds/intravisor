/*
 * cvm_driver.c: core driver methods for managing CVM guests
 *
 * Copyright (C) 2006-2015 Red Hat, Inc.
 * Copyright (C) 2006-2008 Daniel P. Berrange
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

#include <config.h>

#include <sys/types.h>
#include <sys/poll.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
//#include <sys/inotify.h>
#include <sys/un.h>

#include "cvm_driver.h"
#include "cvm_conf.h"
#include "virbuffer.h"
#include "virhostcpu.h"
#include "virhostmem.h"
#include "capabilities.h"
#include "viralloc.h"
#include "viruuid.h"
#include "domain_conf.h"
#include "domain_audit.h"
#include "datatypes.h"
#include "virlog.h"
#include "domain_nwfilter.h"
#include "virfile.h"
#include "virfdstream.h"
#include "configmake.h"
#include "virnetdevtap.h"
#include "virnodesuspend.h"
#include "virprocess.h"
#include "viruri.h"
#include "virstring.h"
#include "viraccessapicheck.h"

#define VIR_FROM_THIS VIR_FROM_CVM

VIR_LOG_INIT("cvm.cvm_driver");

typedef struct _cvmDomainObjPrivate cvmDomainObjPrivate;
typedef cvmDomainObjPrivate *cvmDomainObjPrivatePtr;
struct _cvmDomainObjPrivate {
    int monitor;
    int monitorWatch;
};

static int cvmProcessAutoDestroyInit(struct cvm_driver *driver);
static void cvmProcessAutoDestroyRun(struct cvm_driver *driver,
                                     virConnectPtr conn);
static void cvmProcessAutoDestroyShutdown(struct cvm_driver *driver);
static int cvmProcessAutoDestroyAdd(struct cvm_driver *driver,
                                    virDomainObjPtr vm,
                                    virConnectPtr conn);
static int cvmProcessAutoDestroyRemove(struct cvm_driver *driver,
                                       virDomainObjPtr vm);


static int cvmStateCleanup(void);

static void *cvmDomainObjPrivateAlloc(void *opaque ATTRIBUTE_UNUSED)
{
    cvmDomainObjPrivatePtr priv;

    if (VIR_ALLOC(priv) < 0)
        return NULL;

    priv->monitor = -1;
    priv->monitorWatch = -1;

    return priv;
}

static void cvmDomainObjPrivateFree(void *data)
{
    cvmDomainObjPrivatePtr priv = data;

    VIR_FREE(priv);
}


static void cvmDriverLock(struct cvm_driver *driver)
{
    virMutexLock(&driver->lock);
}
static void cvmDriverUnlock(struct cvm_driver *driver)
{
    virMutexUnlock(&driver->lock);
}


static int cvmOpenMonitor(struct cvm_driver *driver,
                          virDomainObjPtr vm);
static int cvmReadPidFile(struct cvm_driver *driver,
                          virDomainObjPtr vm);

static int cvmStartVMDaemon(virConnectPtr conn,
                            struct cvm_driver *driver,
                            virDomainObjPtr vm,
                            bool autoDestroy);

static void cvmShutdownVMDaemon(struct cvm_driver *driver,
                                virDomainObjPtr vm,
                                virDomainShutoffReason reason);


static int cvmMonitorCommand(const struct cvm_driver *driver,
                             const virDomainObj *vm,
                             const char *cmd,
                             char **reply);

static struct cvm_driver *cvm_driver;

static virDomainObjPtr
cvmDomObjFromDomainLocked(struct cvm_driver *driver,
                          const unsigned char *uuid)
{
    virDomainObjPtr vm;
    char uuidstr[VIR_UUID_STRING_BUFLEN];

    if (!(vm = virDomainObjListFindByUUID(driver->domains, uuid))) {
        virUUIDFormat(uuid, uuidstr);

        virReportError(VIR_ERR_NO_DOMAIN,
                       _("no domain with matching uuid '%s'"), uuidstr);
        return NULL;
    }

    return vm;
}


static virDomainObjPtr
cvmDomObjFromDomain(struct cvm_driver *driver,
                    const unsigned char *uuid)
{
    virDomainObjPtr vm;

    cvmDriverLock(driver);
    vm = cvmDomObjFromDomainLocked(driver, uuid);
    cvmDriverUnlock(driver);
    return vm;
}


struct cvmAutostartData {
    struct cvm_driver *driver;
    virConnectPtr conn;
};

static int
cvmAutostartDomain(virDomainObjPtr vm,
                   void *opaque)
{
    const struct cvmAutostartData *data = opaque;
    int ret = 0;
    virObjectLock(vm);
    if (vm->autostart &&
        !virDomainObjIsActive(vm)) {
        virResetLastError();
        ret = cvmStartVMDaemon(data->conn, data->driver, vm, false);
        virDomainAuditStart(vm, "booted", ret >= 0);
        if (ret < 0) {
            virReportError(VIR_ERR_INTERNAL_ERROR, _("Failed to autostart VM '%s': %s"),
                           vm->def->name, virGetLastErrorMessage());
        } else {
            virObjectEventPtr event =
                virDomainEventLifecycleNewFromObj(vm,
                                         VIR_DOMAIN_EVENT_STARTED,
                                         VIR_DOMAIN_EVENT_STARTED_BOOTED);
            virObjectEventStateQueue(data->driver->domainEventState, event);
        }
    }
    virObjectUnlock(vm);
    return ret;
}

static void
cvmAutostartConfigs(struct cvm_driver *driver)
{
    /* XXX: Figure out a better way todo this. The domain
     * startup code needs a connection handle in order
     * to lookup the bridge associated with a virtual
     * network
     */
    virConnectPtr conn = virConnectOpen(driver->privileged ?
                                        "cvm:///system" :
                                        "cvm:///session");
    /* Ignoring NULL conn which is mostly harmless here */

    struct cvmAutostartData data = { driver, conn };

    cvmDriverLock(driver);
    virDomainObjListForEach(driver->domains, cvmAutostartDomain, &data);
    cvmDriverUnlock(driver);

    virObjectUnref(conn);
}


static int
cvmIdentifyOneChrPTY(struct cvm_driver *driver,
                     virDomainObjPtr dom,
                     virDomainChrDefPtr def,
                     const char *dev)
{
    char *cmd;
    char *res = NULL;
    int retries = 0;
    if (virAsprintf(&cmd, "config %s%d", dev, def->target.port) < 0)
        return -1;
 requery:
    if (cvmMonitorCommand(driver, dom, cmd, &res) < 0)
        return -1;

    if (res && STRPREFIX(res, "pts:")) {
        VIR_FREE(def->source->data.file.path);
        if (VIR_STRDUP(def->source->data.file.path, res + 4) < 0) {
            VIR_FREE(res);
            VIR_FREE(cmd);
            return -1;
        }
    } else if (!res || STRPREFIX(res, "pts")) {
        /* It can take a while to startup, so retry for
           up to 5 seconds */
        /* XXX should do this in a better non-blocking
           way somehow ...perhaps register a timer */
        if (retries++ < 50) {
            VIR_FREE(res);
            usleep(1000*10);
            goto requery;
        }
    }

    VIR_FREE(cmd);
    VIR_FREE(res);
    return 0;
}

static int
cvmIdentifyChrPTY(struct cvm_driver *driver,
                  virDomainObjPtr dom)
{
    size_t i;

    for (i = 0; i < dom->def->nconsoles; i++)
        if (dom->def->consoles[i]->source->type == VIR_DOMAIN_CHR_TYPE_PTY)
        if (cvmIdentifyOneChrPTY(driver, dom,
                                 dom->def->consoles[i], "con") < 0)
            return -1;

    for (i = 0; i < dom->def->nserials; i++)
        if (dom->def->serials[i]->source->type == VIR_DOMAIN_CHR_TYPE_PTY &&
            cvmIdentifyOneChrPTY(driver, dom,
                                 dom->def->serials[i], "ssl") < 0)
            return -1;

    return 0;
}

static void
cvmInotifyEvent(int watch,
                int fd,
                int events ATTRIBUTE_UNUSED,
                void *data)
{
#if 0
    char buf[1024];
    struct inotify_event e;
    int got;
    char *tmp, *name;
    struct cvm_driver *driver = data;
    virDomainObjPtr dom;
    virObjectEventPtr event = NULL;

    cvmDriverLock(driver);
    if (watch != driver->inotifyWatch)
        goto cleanup;

 reread:
    got = read(fd, buf, sizeof(buf));
    if (got == -1) {
        if (errno == EINTR)
            goto reread;
        goto cleanup;
    }

    tmp = buf;
    while (got) {
        if (got < sizeof(e))
            goto cleanup; /* bad */

        memcpy(&e, tmp, sizeof(e));
        tmp += sizeof(e);
        got -= sizeof(e);

        if (got < e.len)
            goto cleanup;

        tmp += e.len;
        got -= e.len;

        name = (char *)&(e.name);

        dom = virDomainObjListFindByName(driver->domains, name);

        if (!dom)
            continue;

        if (e.mask & IN_DELETE) {
            VIR_DEBUG("Got inotify domain shutdown '%s'", name);
            if (!virDomainObjIsActive(dom)) {
                virDomainObjEndAPI(&dom);
                continue;
            }

            cvmShutdownVMDaemon(driver, dom, VIR_DOMAIN_SHUTOFF_SHUTDOWN);
            virDomainAuditStop(dom, "shutdown");
            event = virDomainEventLifecycleNewFromObj(dom,
                                             VIR_DOMAIN_EVENT_STOPPED,
                                             VIR_DOMAIN_EVENT_STOPPED_SHUTDOWN);
            if (!dom->persistent)
                virDomainObjListRemove(driver->domains, dom);
        } else if (e.mask & (IN_CREATE | IN_MODIFY)) {
            VIR_DEBUG("Got inotify domain startup '%s'", name);
            if (virDomainObjIsActive(dom)) {
                virDomainObjEndAPI(&dom);
                continue;
            }

            if (cvmReadPidFile(driver, dom) < 0) {
                virDomainObjEndAPI(&dom);
                continue;
            }

            dom->def->id = driver->nextvmid++;

            if (!driver->nactive && driver->inhibitCallback)
                driver->inhibitCallback(true, driver->inhibitOpaque);
            driver->nactive++;

            virDomainObjSetState(dom, VIR_DOMAIN_RUNNING,
                                 VIR_DOMAIN_RUNNING_BOOTED);

            if (cvmOpenMonitor(driver, dom) < 0) {
                VIR_WARN("Could not open monitor for new domain");
                cvmShutdownVMDaemon(driver, dom,
                                    VIR_DOMAIN_SHUTOFF_FAILED);
                virDomainAuditStop(dom, "failed");
                event = virDomainEventLifecycleNewFromObj(dom,
                                                 VIR_DOMAIN_EVENT_STOPPED,
                                                 VIR_DOMAIN_EVENT_STOPPED_FAILED);
                if (!dom->persistent)
                    virDomainObjListRemove(driver->domains, dom);
            } else if (cvmIdentifyChrPTY(driver, dom) < 0) {
                VIR_WARN("Could not identify character devices for new domain");
                cvmShutdownVMDaemon(driver, dom,
                                    VIR_DOMAIN_SHUTOFF_FAILED);
                virDomainAuditStop(dom, "failed");
                event = virDomainEventLifecycleNewFromObj(dom,
                                                 VIR_DOMAIN_EVENT_STOPPED,
                                                 VIR_DOMAIN_EVENT_STOPPED_FAILED);
                if (!dom->persistent)
                    virDomainObjListRemove(driver->domains, dom);
            }
        }
        virDomainObjEndAPI(&dom);

        virObjectEventStateQueue(driver->domainEventState, event);
        event = NULL;
    }

 cleanup:
    cvmDriverUnlock(driver);
#else
	printf("NOT IMPLEMENTED %s\n", __func__);
#endif
}


static int
cvmDomainDeviceDefPostParse(virDomainDeviceDefPtr dev,
                            const virDomainDef *def ATTRIBUTE_UNUSED,
                            virCapsPtr caps ATTRIBUTE_UNUSED,
                            unsigned int parseFlags ATTRIBUTE_UNUSED,
                            void *opaque ATTRIBUTE_UNUSED,
                            void *parseOpaque ATTRIBUTE_UNUSED)
{
    if (dev->type == VIR_DOMAIN_DEVICE_CHR &&
        dev->data.chr->deviceType == VIR_DOMAIN_CHR_DEVICE_TYPE_CONSOLE &&
        dev->data.chr->targetType == VIR_DOMAIN_CHR_CONSOLE_TARGET_TYPE_NONE)
        dev->data.chr->targetType = VIR_DOMAIN_CHR_CONSOLE_TARGET_TYPE_CVM;

    /* forbid capabilities mode hostdev in this kind of hypervisor */
    if (dev->type == VIR_DOMAIN_DEVICE_HOSTDEV &&
        dev->data.hostdev->mode == VIR_DOMAIN_HOSTDEV_MODE_CAPABILITIES) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                       _("hostdev mode 'capabilities' is not "
                         "supported in %s"),
                       virDomainVirtTypeToString(def->virtType));

        return -1;
    }

    return 0;
}


static int
cvmDomainDefPostParse(virDomainDefPtr def ATTRIBUTE_UNUSED,
                      virCapsPtr caps ATTRIBUTE_UNUSED,
                      unsigned int parseFlags ATTRIBUTE_UNUSED,
                      void *opaque ATTRIBUTE_UNUSED,
                      void *parseOpaque ATTRIBUTE_UNUSED)
{
    return 0;
}


virDomainDefParserConfig cvmDriverDomainDefParserConfig = {
    .devicesPostParseCallback = cvmDomainDeviceDefPostParse,
    .domainPostParseCallback = cvmDomainDefPostParse,
};


/**
 * cvmStartup:
 *
 * Initialization function for the Uml daemon
 */
static int
cvmStateInitialize(bool privileged,
                   virStateInhibitCallback callback,
                   void *opaque)
{
    char *base = NULL;
    char *userdir = NULL;
    virDomainXMLPrivateDataCallbacks privcb = {
        .alloc = cvmDomainObjPrivateAlloc,
        .free = cvmDomainObjPrivateFree,
    };

    if (VIR_ALLOC(cvm_driver) < 0)
        return -1;

    cvm_driver->privileged = privileged;
    cvm_driver->inhibitCallback = callback;
    cvm_driver->inhibitOpaque = opaque;

    if (virMutexInit(&cvm_driver->lock) < 0) {
        VIR_FREE(cvm_driver);
        return -1;
    }
    cvmDriverLock(cvm_driver);

    /* Don't have a dom0 so start from 1 */
    cvm_driver->nextvmid = 1;
    cvm_driver->inotifyWatch = -1;

    if (!(cvm_driver->domains = virDomainObjListNew()))
        goto error;

    cvm_driver->domainEventState = virObjectEventStateNew();
    if (!cvm_driver->domainEventState)
        goto error;

#if 0
    userdir = virGetUserDirectory();
    if (!userdir)
        goto error;
#endif

    if (privileged) {
        if (virAsprintf(&cvm_driver->logDir,
                        "%s/log/libvirt/cvm", LOCALSTATEDIR) == -1)
            goto out_of_memory;

        if (VIR_STRDUP(base, SYSCONFDIR "/libvirt") < 0)
            goto error;

        if (virAsprintf(&cvm_driver->monitorDir,
                        "%s/run/libvirt/cvm-guest", LOCALSTATEDIR) == -1)
            goto out_of_memory;
    } else {

#if 0
        base = virGetUserConfigDirectory();
        if (!base)
            goto error;
#else
	base = "/";
#endif
        if (virAsprintf(&cvm_driver->logDir,
                        "%s/cvm/log", base) == -1)
            goto out_of_memory;

#if 0
        if (virAsprintf(&cvm_driver->monitorDir,
                        "%s/.cvm", userdir) == -1)
#else
        if (virAsprintf(&cvm_driver->monitorDir,
                        "%s/.cvm", "/") == -1)
#endif
            goto out_of_memory;
    }

    /* Configuration paths are either $XDG_CONFIG_HOME/libvirt/cvm/... (session) or
     * /etc/libvirt/cvm/... (system).
     */
    if (virAsprintf(&cvm_driver->configDir, "%s/cvm", base) == -1)
        goto out_of_memory;

    if (virAsprintf(&cvm_driver->autostartDir, "%s/cvm/autostart", base) == -1)
        goto out_of_memory;

//    VIR_FREE(base);

    if ((cvm_driver->caps = cvmCapsInit()) == NULL)
        goto out_of_memory;

    if (!(cvm_driver->xmlopt = virDomainXMLOptionNew(&cvmDriverDomainDefParserConfig,
                                                     &privcb, NULL, NULL, NULL)))
        goto error;

#if 0
    if ((cvm_driver->inotifyFD = inotify_init()) < 0) {
        virReportError(VIR_ERR_INTERNAL_ERROR, "%s", _("cannot initialize inotify"));
        goto error;
    }
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

#if 0
    if (virFileMakePath(cvm_driver->monitorDir) < 0) {
        virReportSystemError(errno, _("Failed to create monitor directory %s"),
                             cvm_driver->monitorDir);
        goto error;
    }
#endif
#if 0
    VIR_INFO("Adding inotify watch on %s", cvm_driver->monitorDir);
    if (inotify_add_watch(cvm_driver->inotifyFD,
                          cvm_driver->monitorDir,
                          IN_CREATE | IN_MODIFY | IN_DELETE) < 0) {
        virReportSystemError(errno, _("Failed to create inotify watch on %s"),
                             cvm_driver->monitorDir);
        goto error;
    }

    if ((cvm_driver->inotifyWatch =
         virEventAddHandle(cvm_driver->inotifyFD, POLLIN,
                           cvmInotifyEvent, cvm_driver, NULL)) < 0)
        goto error;
#else
    printf("skipping not implemented at %d %s\n", __LINE__, __FILE__);
#endif
    if (cvmProcessAutoDestroyInit(cvm_driver) < 0)
        goto error;
#if 0
    if (virDomainObjListLoadAllConfigs(cvm_driver->domains,
                                       cvm_driver->configDir,
                                       cvm_driver->autostartDir, false,
                                       cvm_driver->caps,
                                       cvm_driver->xmlopt,
                                       NULL, NULL) < 0)
        goto error;
#endif
    cvmDriverUnlock(cvm_driver);

//    VIR_FREE(userdir);

    return 0;

 out_of_memory:
    virReportError(VIR_ERR_INTERNAL_ERROR, "%s", _("cvmStartup: out of memory"));

 error:
    VIR_FREE(userdir);
    VIR_FREE(base);
    cvmDriverUnlock(cvm_driver);
    cvmStateCleanup();
    return -1;
}

/**
 * cvmStateAutoStart:
 *
 * Function to autostart the Uml daemons
 */
static void
cvmStateAutoStart(void)
{
    if (!cvm_driver)
        return;

    cvmAutostartConfigs(cvm_driver);
}

static void cvmNotifyLoadDomain(virDomainObjPtr vm, int newVM, void *opaque)
{
    struct cvm_driver *driver = opaque;

    if (newVM) {
        virObjectEventPtr event =
            virDomainEventLifecycleNewFromObj(vm,
                                     VIR_DOMAIN_EVENT_DEFINED,
                                     VIR_DOMAIN_EVENT_DEFINED_ADDED);
        virObjectEventStateQueue(driver->domainEventState, event);
    }
}


/**
 * cvmStateReload:
 *
 * Function to restart the Uml daemon, it will recheck the configuration
 * files and update its state and the networking
 */
static int
cvmStateReload(void)
{
    if (!cvm_driver)
        return 0;

    cvmDriverLock(cvm_driver);
    virDomainObjListLoadAllConfigs(cvm_driver->domains,
                                   cvm_driver->configDir,
                                   cvm_driver->autostartDir, false,
                                   cvm_driver->caps,
                                   cvm_driver->xmlopt,
                                   cvmNotifyLoadDomain, cvm_driver);
    cvmDriverUnlock(cvm_driver);

    return 0;
}


static int
cvmShutdownOneVM(virDomainObjPtr dom, void *opaque)
{
    struct cvm_driver *driver = opaque;

    virObjectLock(dom);
    if (virDomainObjIsActive(dom)) {
        cvmShutdownVMDaemon(driver, dom, VIR_DOMAIN_SHUTOFF_SHUTDOWN);
        virDomainAuditStop(dom, "shutdown");
    }
    virObjectUnlock(dom);
    return 0;
}

/**
 * cvmStateCleanup:
 *
 * Shutdown the Uml daemon, it will stop all active domains and networks
 */
static int
cvmStateCleanup(void)
{
    if (!cvm_driver)
        return -1;

    cvmDriverLock(cvm_driver);
    if (cvm_driver->inotifyWatch != -1)
        virEventRemoveHandle(cvm_driver->inotifyWatch);
    VIR_FORCE_CLOSE(cvm_driver->inotifyFD);
    virObjectUnref(cvm_driver->caps);
    virObjectUnref(cvm_driver->xmlopt);

    /* shutdown active VMs
     * XXX allow them to stay around & reconnect */
    virDomainObjListForEach(cvm_driver->domains, cvmShutdownOneVM, cvm_driver);

    virObjectUnref(cvm_driver->domains);

    virObjectUnref(cvm_driver->domainEventState);

    VIR_FREE(cvm_driver->logDir);
    VIR_FREE(cvm_driver->configDir);
    VIR_FREE(cvm_driver->autostartDir);
    VIR_FREE(cvm_driver->monitorDir);

    cvmProcessAutoDestroyShutdown(cvm_driver);

    cvmDriverUnlock(cvm_driver);
    virMutexDestroy(&cvm_driver->lock);
    VIR_FREE(cvm_driver);

    return 0;
}


static int cvmProcessAutoDestroyInit(struct cvm_driver *driver)
{
    if (!(driver->autodestroy = virHashCreate(5, NULL)))
        return -1;

    return 0;
}

struct cvmProcessAutoDestroyData {
    struct cvm_driver *driver;
    virConnectPtr conn;
};

static int cvmProcessAutoDestroyDom(void *payload,
                                    const void *name,
                                    void *opaque)
{
    struct cvmProcessAutoDestroyData *data = opaque;
    virConnectPtr conn = payload;
    const char *uuidstr = name;
    unsigned char uuid[VIR_UUID_BUFLEN];
    virDomainObjPtr dom;
    virObjectEventPtr event = NULL;

    VIR_DEBUG("conn=%p uuidstr=%s thisconn=%p", conn, uuidstr, data->conn);

    if (data->conn != conn)
        return 0;

    if (virUUIDParse(uuidstr, uuid) < 0) {
        VIR_WARN("Failed to parse %s", uuidstr);
        return 0;
    }

    if (!(dom = virDomainObjListFindByUUID(data->driver->domains, uuid))) {
        VIR_DEBUG("No domain object to kill");
        return 0;
    }

    VIR_DEBUG("Killing domain");
    cvmShutdownVMDaemon(data->driver, dom, VIR_DOMAIN_SHUTOFF_DESTROYED);
    virDomainAuditStop(dom, "destroyed");
    event = virDomainEventLifecycleNewFromObj(dom,
                                     VIR_DOMAIN_EVENT_STOPPED,
                                     VIR_DOMAIN_EVENT_STOPPED_DESTROYED);

    if (!dom->persistent)
        virDomainObjListRemove(data->driver->domains, dom);

#if 1
    virDomainObjEndAPI(&dom);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    virObjectEventStateQueue(data->driver->domainEventState, event);
    virHashRemoveEntry(data->driver->autodestroy, uuidstr);
    return 0;
}

/*
 * Precondition: driver is locked
 */
static void cvmProcessAutoDestroyRun(struct cvm_driver *driver, virConnectPtr conn)
{
    struct cvmProcessAutoDestroyData data = {
        driver, conn
    };
    VIR_DEBUG("conn=%p", conn);
    virHashForEach(driver->autodestroy, cvmProcessAutoDestroyDom, &data);
}

static void cvmProcessAutoDestroyShutdown(struct cvm_driver *driver)
{
    virHashFree(driver->autodestroy);
}

static int cvmProcessAutoDestroyAdd(struct cvm_driver *driver,
                                    virDomainObjPtr vm,
                                    virConnectPtr conn)
{
    char uuidstr[VIR_UUID_STRING_BUFLEN];
    virUUIDFormat(vm->def->uuid, uuidstr);
    VIR_DEBUG("vm=%s uuid=%s conn=%p", vm->def->name, uuidstr, conn);
    if (virHashAddEntry(driver->autodestroy, uuidstr, conn) < 0)
        return -1;
    return 0;
}

static int cvmProcessAutoDestroyRemove(struct cvm_driver *driver,
                                       virDomainObjPtr vm)
{
    char uuidstr[VIR_UUID_STRING_BUFLEN];
    virUUIDFormat(vm->def->uuid, uuidstr);
    VIR_DEBUG("vm=%s uuid=%s", vm->def->name, uuidstr);
    if (virHashRemoveEntry(driver->autodestroy, uuidstr) < 0)
        return -1;
    return 0;
}


static int cvmReadPidFile(struct cvm_driver *driver,
                          virDomainObjPtr vm)
{
    int rc = -1;
    FILE *file;
    char *pidfile = NULL;
    int retries = 0;

    vm->pid = -1;
    if (virAsprintf(&pidfile, "%s/%s/pid",
                    driver->monitorDir, vm->def->name) < 0)
        return -1;

 reopen:
    if (!(file = fopen(pidfile, "r"))) {
        if (errno == ENOENT &&
            retries++ < 50) {
            usleep(1000 * 100);
            goto reopen;
        }
        goto cleanup;
    }

    if (fscanf(file, "%d", &vm->pid) != 1) {
        errno = EINVAL;
        VIR_FORCE_FCLOSE(file);
        goto cleanup;
    }

    if (VIR_FCLOSE(file) < 0)
        goto cleanup;

    rc = 0;

 cleanup:
    if (rc != 0)
        virReportSystemError(errno,
                             _("failed to read pid: %s"),
                             pidfile);
    VIR_FREE(pidfile);
    return rc;
}

static int cvmMonitorAddress(const struct cvm_driver *driver,
                             const virDomainObj *vm,
                             struct sockaddr_un *addr)
{
    char *sockname;
    int retval = 0;

    if (virAsprintf(&sockname, "%s/%s/mconsole",
                    driver->monitorDir, vm->def->name) < 0)
        return -1;

    memset(addr, 0, sizeof(*addr));
    addr->sun_family = AF_UNIX;
    if (virStrcpyStatic(addr->sun_path, sockname) < 0) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Unix path %s too long for destination"), sockname);
        retval = -1;
    }
    VIR_FREE(sockname);
    return retval;
}

static int cvmOpenMonitor(struct cvm_driver *driver,
                          virDomainObjPtr vm)
{
    struct sockaddr_un addr;
    struct stat sb;
    int retries = 0;
    cvmDomainObjPrivatePtr priv = vm->privateData;

    if (cvmMonitorAddress(driver, vm, &addr) < 0)
        return -1;

    VIR_DEBUG("Dest address for monitor is '%s'", addr.sun_path);
 restat:
    if (stat(addr.sun_path, &sb) < 0) {
        if (errno == ENOENT &&
            retries++ < 50) {
            usleep(1000 * 100);
            goto restat;
        }
        return -1;
    }

    if ((priv->monitor = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
        virReportSystemError(errno,
                             "%s", _("cannot open socket"));
        return -1;
    }

    memset(addr.sun_path, 0, sizeof(addr.sun_path));
    snprintf(addr.sun_path + 1, sizeof(addr.sun_path) - 1,
             "libvirt-cvm-%u", vm->pid);
    VIR_DEBUG("Reply address for monitor is '%s'", addr.sun_path+1);
    if (bind(priv->monitor, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        virReportSystemError(errno,
                             "%s", _("cannot bind socket"));
        VIR_FORCE_CLOSE(priv->monitor);
        return -1;
    }

    return 0;
}


#define MONITOR_MAGIC 0xcafebabe
#define MONITOR_BUFLEN 512
#define MONITOR_VERSION 2

struct monitor_request {
    uint32_t magic;
    uint32_t version;
    uint32_t length;
    char data[MONITOR_BUFLEN];
};

struct monitor_response {
    uint32_t error;
    uint32_t extra;
    uint32_t length;
    char data[MONITOR_BUFLEN];
};


static int cvmMonitorCommand(const struct cvm_driver *driver,
                             const virDomainObj *vm,
                             const char *cmd,
                             char **reply)
{
    struct monitor_request req;
    struct monitor_response res;
    char *retdata = NULL;
    int retlen = 0, ret = 0;
    struct sockaddr_un addr;
    unsigned int addrlen;
    cvmDomainObjPrivatePtr priv = vm->privateData;

    VIR_DEBUG("Run command '%s'", cmd);

    *reply = NULL;

    if (cvmMonitorAddress(driver, vm, &addr) < 0)
        return -1;

    memset(&req, 0, sizeof(req));
    req.magic = MONITOR_MAGIC;
    req.version = MONITOR_VERSION;
    req.length = strlen(cmd);
    if (req.length > (MONITOR_BUFLEN-1)) {
        virReportSystemError(EINVAL,
                             _("cannot send too long command %s (%d bytes)"),
                             cmd, req.length);
        return -1;
    }
    if (virStrcpyStatic(req.data, cmd) < 0) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Command %s too long for destination"), cmd);
        return -1;
    }

    if (sendto(priv->monitor, &req, sizeof(req), 0,
               (struct sockaddr *)&addr, sizeof(addr)) != sizeof(req)) {
        virReportSystemError(errno,
                             _("cannot send command %s"),
                             cmd);
        return -1;
    }

    do {
        ssize_t nbytes;
        addrlen = sizeof(addr);
        nbytes = recvfrom(priv->monitor, &res, sizeof(res), 0,
                          (struct sockaddr *)&addr, &addrlen);
        if (nbytes < 0) {
            if (errno == EAGAIN || errno == EINTR)
                continue;
            virReportSystemError(errno, _("cannot read reply %s"), cmd);
            goto error;
        }
        /* Ensure res.length is safe to read before validating its value.  */
        if (nbytes < offsetof(struct monitor_request, data) ||
            nbytes < offsetof(struct monitor_request, data) + res.length) {
            virReportSystemError(0, _("incomplete reply %s"), cmd);
            goto error;
        }

        if (VIR_REALLOC_N(retdata, retlen + res.length) < 0)
            goto error;
        memcpy(retdata + retlen, res.data, res.length);
        retlen += res.length - 1;
        retdata[retlen] = '\0';

        if (res.error)
            ret = -1;

    } while (res.extra);

    VIR_DEBUG("Command reply is '%s'", NULLSTR(retdata));

    if (ret < 0)
        VIR_FREE(retdata);
    else
        *reply = retdata;

    return ret;

 error:
    VIR_FREE(retdata);
    return -1;
}


static void cvmCleanupTapDevices(virDomainObjPtr vm)
{
    size_t i;

    for (i = 0; i < vm->def->nnets; i++) {
        virDomainNetDefPtr def = vm->def->nets[i];

        if (def->type != VIR_DOMAIN_NET_TYPE_BRIDGE &&
            def->type != VIR_DOMAIN_NET_TYPE_NETWORK)
            continue;

#if 0
        ignore_value(virNetDevTapDelete(def->ifname,
                                        def->backend.tap));
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    }
}

static int cvmStartVMDaemon(virConnectPtr conn,
                            struct cvm_driver *driver,
                            virDomainObjPtr vm,
                            bool autoDestroy)
{
    int ret = -1;
    char *logfile;
    int logfd = -1;
    cvmDomainObjPrivatePtr priv = vm->privateData;
    virCommandPtr cmd = NULL;
    size_t i;

    if (virDomainObjIsActive(vm)) {
        virReportError(VIR_ERR_OPERATION_INVALID, "%s",
                       _("VM is already active"));
        return -1;
    }

    if (!vm->def->os.kernel) {
        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
                       _("no kernel specified"));
        return -1;
    }

#if 0
    /* Make sure the binary we are about to try exec'ing exists.
     * Technically we could catch the exec() failure, but that's
     * in a sub-process so its hard to feed back a useful error
     */
    if (!virFileIsExecutable(vm->def->os.kernel)) {
        virReportSystemError(errno,
                             _("Cannot find CVM kernel %s"),
                             vm->def->os.kernel);
        return -1;
    }

    if (virFileMakePath(driver->logDir) < 0) {
        virReportSystemError(errno,
                             _("cannot create log directory %s"),
                             driver->logDir);
        return -1;
    }
#endif
    if (virAsprintf(&logfile, "/%s.log", vm->def->name) < 0)
        return -1;

    if ((logfd = open(logfile, O_CREAT | O_TRUNC | O_WRONLY,
                      S_IRUSR | S_IWUSR)) < 0) {
        virReportSystemError(errno,
                             _("failed to create logfile %s"),
                             logfile);
        VIR_FREE(logfile);
        return -1;
    }
    VIR_FREE(logfile);

    if (virSetCloseExec(logfd) < 0) {
        virReportSystemError(errno, "%s",
                             _("Unable to set VM logfile close-on-exec flag"));
        VIR_FORCE_CLOSE(logfd);
        return -1;
    }

    /* Do this upfront, so any part of the startup process can add
     * runtime state to vm->def that won't be persisted. This let's us
     * report implicit runtime defaults in the XML, like vnc listen/socket
     */
    VIR_DEBUG("Setting current domain def as transient");
    if (virDomainObjSetDefTransient(driver->caps, driver->xmlopt, vm) < 0) {
        VIR_FORCE_CLOSE(logfd);
        return -1;
    }

#if 0
    if (!(cmd = cvmBuildCommandLine(conn, driver, vm)))
        goto cleanup;
#endif

    for (i = 0; i < vm->def->nconsoles; i++) {
        VIR_FREE(vm->def->consoles[i]->info.alias);
        if (virAsprintf(&vm->def->consoles[i]->info.alias, "console%zu", i) < 0)
            goto cleanup;
    }

#if 0
    virCommandWriteArgLog(cmd, logfd);

    priv->monitor = -1;

    virCommandClearCaps(cmd);
    virCommandSetOutputFD(cmd, &logfd);
    virCommandSetErrorFD(cmd, &logfd);
    virCommandDaemonize(cmd);


    virReportSystemError(errno,
                             _("ready to run command `%s`"),
                             cmd);


    if (virCommandRun(cmd, NULL) < 0)
        goto cleanup;
#else
#if 0
    time_t current_time;
    struct tm *time_info;
    char filename[30];
    FILE *file;

    // Get the current timestamp
    time(&current_time);
    time_info = localtime(&current_time);

    // Format the timestamp as a string
//    strftime(filename, sizeof(filename), "/tmp/%Y%m%d%H%M%S.yaml", time_info);

    snprintf(filename, sizeof(filename), "/1.yaml");

    // Create and open the file
    file = fopen(filename, "w");
    if (file == NULL) {
	    virReportSystemError(errno,
                             _("failed to create file `%s`"),
                             filename);

	while(1);
    }

	fprintf(file, "---\ncVMs:\n- name: %s\n  disk: %s\n  runtime: %s\n  args: %s\n  callback_out: %s\n  isolation:\n  - base: %s\n    size: %s\n    begin: %s\n    end: %s\n",
		vm->def->name, vm->def->os.disk, vm->def->os.kernel, vm->def->os.cmdline, vm->def->os.callback_out, vm->def->os.base, vm->def->os.size, vm->def->os.begin, vm->def->os.end);
    fclose(file);

    extern int parse_and_spawn_yaml(char *yaml_cfg, char a);
    vm->pid=parse_and_spawn_yaml(filename, 1);
#else
	char yaml[4096];
	int len = snprintf(yaml, 4096, "---\ncVMs:\n- name: %s\n  disk: %s\n  runtime: %s\n  args: %s\n  callback_out: %s\n  isolation:\n  - base: %s\n    size: %s\n    begin: %s\n    end: %s\n",
		vm->def->name, vm->def->os.disk, vm->def->os.kernel, vm->def->os.cmdline, vm->def->os.callback_out, vm->def->os.base, vm->def->os.size, vm->def->os.begin, vm->def->os.end);

    extern int parse_and_spawn_yaml(char *yaml_cfg, char a);
    vm->pid=parse_and_spawn_yaml(yaml, len);
    
#endif
            vm->def->id = driver->nextvmid++;

            if (!driver->nactive && driver->inhibitCallback)
                driver->inhibitCallback(true, driver->inhibitOpaque);
            driver->nactive++;

            virDomainObjSetState(vm, VIR_DOMAIN_RUNNING,
                                 VIR_DOMAIN_RUNNING_BOOTED);

#if 0
            if (cvmOpenMonitor(driver, vm) < 0) {
                VIR_WARN("Could not open monitor for new domain");
                cvmShutdownVMDaemon(driver, vm,
                                    VIR_DOMAIN_SHUTOFF_FAILED);
                virDomainAuditStop(vm, "failed");
//                event = virDomainEventLifecycleNewFromObj(vm,
//                                                 VIR_DOMAIN_EVENT_STOPPED,
//                                                 VIR_DOMAIN_EVENT_STOPPED_FAILED);
                if (!vm->persistent)
                    virDomainObjListRemove(driver->domains, vm);
            } else 
#endif
#if 0
if (cvmIdentifyChrPTY(driver, vm) < 0) {
                VIR_WARN("Could not identify character devices for new domain");
                cvmShutdownVMDaemon(driver, vm,
                                    VIR_DOMAIN_SHUTOFF_FAILED);
                virDomainAuditStop(vm, "failed");
//                event = virDomainEventLifecycleNewFromObj(vm,
//                                                 VIR_DOMAIN_EVENT_STOPPED,
//                                                 VIR_DOMAIN_EVENT_STOPPED_FAILED);
                if (!vm->persistent)
                    virDomainObjListRemove(driver->domains, vm);
            }
#endif

#endif
    if (autoDestroy &&
        cvmProcessAutoDestroyAdd(driver, vm, conn) < 0)
        goto cleanup;

    ret = 0;
 cleanup:
//    VIR_FORCE_CLOSE(logfd);
//    virCommandFree(cmd);

    if (ret < 0) {
        virDomainConfVMNWFilterTeardown(vm);
        cvmCleanupTapDevices(vm);
        virDomainObjRemoveTransientDef(vm);
    }

    /* NB we don't mark it running here - we do that async
       with inotify */
    /* XXX what if someone else tries to start it again
       before we get the inotification ? Sounds like
       trouble.... */
    /* XXX this is bad for events too. must fix this better */

    return ret;
}

static void cvmShutdownVMDaemon(struct cvm_driver *driver,
                                virDomainObjPtr vm,
                                virDomainShutoffReason reason)
{
    int ret;
    cvmDomainObjPrivatePtr priv = vm->privateData;

    if (!virDomainObjIsActive(vm))
        return;

    virProcessKill(vm->pid, SIGTERM);

    VIR_FORCE_CLOSE(priv->monitor);

    if ((ret = waitpid(vm->pid, NULL, 0)) != vm->pid) {
        VIR_WARN("Got unexpected pid %d != %d",
               ret, vm->pid);
    }

    vm->pid = -1;
    vm->def->id = -1;
#if 1
    virDomainObjSetState(vm, VIR_DOMAIN_SHUTOFF, reason);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    virDomainConfVMNWFilterTeardown(vm);
    cvmCleanupTapDevices(vm);

    /* Stop autodestroy in case guest is restarted */
    cvmProcessAutoDestroyRemove(driver, vm);

#if 1
    virDomainObjRemoveTransientDef(vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    driver->nactive--;
    if (!driver->nactive && driver->inhibitCallback)
        driver->inhibitCallback(false, driver->inhibitOpaque);
}


static int cvmConnectURIProbe(char **uri)
{
    if (cvm_driver == NULL)
        return 0;

    return VIR_STRDUP(*uri, cvm_driver->privileged ?
                      "cvm:///system" :
                      "cvm:///session");
}


static virDrvOpenStatus cvmConnectOpen(virConnectPtr conn,
                                       virConnectAuthPtr auth ATTRIBUTE_UNUSED,
                                       virConfPtr conf ATTRIBUTE_UNUSED,
                                       unsigned int flags)
{
    virCheckFlags(VIR_CONNECT_RO, VIR_DRV_OPEN_ERROR);
    /* URI was good, but driver isn't active */
    if (cvm_driver == NULL) {
        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
                       _("cvm state driver is not active"));
        return VIR_DRV_OPEN_ERROR;
    }
    /* Check path and tell them correct path if they made a mistake */
    if (cvm_driver->privileged) {
        if (STRNEQ(conn->uri->path, "/system") &&
            STRNEQ(conn->uri->path, "/session")) {
            virReportError(VIR_ERR_INTERNAL_ERROR,
                           _("unexpected CVM URI path '%s', try cvm:///system"),
                           conn->uri->path);
            return VIR_DRV_OPEN_ERROR;
        }
    } else {
        if (STRNEQ(conn->uri->path, "/session")) {
            virReportError(VIR_ERR_INTERNAL_ERROR,
                           _("unexpected CVM URI path '%s', try cvm:///session"),
                           conn->uri->path);
            return VIR_DRV_OPEN_ERROR;
        }
    }
    if (virConnectOpenEnsureACL(conn) < 0)
        return VIR_DRV_OPEN_ERROR;
    conn->privateData = cvm_driver;
    return VIR_DRV_OPEN_SUCCESS;
}

static int cvmConnectClose(virConnectPtr conn)
{
    struct cvm_driver *driver = conn->privateData;

    cvmDriverLock(driver);
    cvmProcessAutoDestroyRun(driver, conn);
    cvmDriverUnlock(driver);

    conn->privateData = NULL;

    return 0;
}

static const char *cvmConnectGetType(virConnectPtr conn) {
    if (virConnectGetTypeEnsureACL(conn) < 0)
        return NULL;

    return "CVM";
}


static int cvmConnectIsSecure(virConnectPtr conn ATTRIBUTE_UNUSED)
{
    /* Trivially secure, since always inside the daemon */
    return 1;
}


static int cvmConnectIsEncrypted(virConnectPtr conn ATTRIBUTE_UNUSED)
{
    /* Not encrypted, but remote driver takes care of that */
    return 0;
}


static int cvmConnectIsAlive(virConnectPtr conn ATTRIBUTE_UNUSED)
{
    return 1;
}


static char *cvmConnectGetCapabilities(virConnectPtr conn) {
    struct cvm_driver *driver = (struct cvm_driver *)conn->privateData;
    char *xml;

    if (virConnectGetCapabilitiesEnsureACL(conn) < 0)
        return NULL;

    cvmDriverLock(driver);
    xml = virCapabilitiesFormatXML(driver->caps);
    cvmDriverUnlock(driver);

    return xml;
}



static int cvmGetProcessInfo(unsigned long long *cpuTime, pid_t pid)
{
    char *proc;
    FILE *pidinfo;
    unsigned long long usertime, systime;

    if (virAsprintf(&proc, "/proc/%lld/stat", (long long)pid) < 0)
        return -1;

    if (!(pidinfo = fopen(proc, "r"))) {
        /* VM probably shut down, so fake 0 */
        *cpuTime = 0;
        VIR_FREE(proc);
        return 0;
    }

    VIR_FREE(proc);

    if (fscanf(pidinfo, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %llu %llu", &usertime, &systime) != 2) {
        cvmDebug("not enough arg");
        VIR_FORCE_FCLOSE(pidinfo);
        return -1;
    }

    /* We got jiffies
     * We want nanoseconds
     * _SC_CLK_TCK is jiffies per second
     * So calculate thus....
     */
    *cpuTime = 1000ull * 1000ull * 1000ull * (usertime + systime) / (unsigned long long)sysconf(_SC_CLK_TCK);

    cvmDebug("Got %llu %llu %llu", usertime, systime, *cpuTime);

    VIR_FORCE_FCLOSE(pidinfo);

    return 0;
}


static virDomainPtr cvmDomainLookupByID(virConnectPtr conn,
                                          int id)
{
    struct cvm_driver *driver = (struct cvm_driver *)conn->privateData;
    virDomainObjPtr vm;
    virDomainPtr dom = NULL;

    cvmDriverLock(driver);
    vm = virDomainObjListFindByID(driver->domains, id);
    cvmDriverUnlock(driver);

    if (!vm) {
        virReportError(VIR_ERR_NO_DOMAIN,
                       _("no domain with matching id '%d'"), id);
        goto cleanup;
    }

    if (virDomainLookupByIDEnsureACL(conn, vm->def) < 0)
        goto cleanup;

    dom = virGetDomain(conn, vm->def->name, vm->def->uuid, vm->def->id);

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return dom;
}

static virDomainPtr cvmDomainLookupByUUID(virConnectPtr conn,
                                          const unsigned char *uuid)
{
    struct cvm_driver *driver = (struct cvm_driver *)conn->privateData;
    virDomainObjPtr vm;
    virDomainPtr dom = NULL;

    if (!(vm = cvmDomObjFromDomain(driver, uuid)))
        return NULL;

    if (virDomainLookupByUUIDEnsureACL(conn, vm->def) < 0)
        goto cleanup;

    dom = virGetDomain(conn, vm->def->name, vm->def->uuid, vm->def->id);

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return dom;
}

static virDomainPtr cvmDomainLookupByName(virConnectPtr conn,
                                            const char *name)
{
    struct cvm_driver *driver = (struct cvm_driver *)conn->privateData;
    virDomainObjPtr vm;
    virDomainPtr dom = NULL;

    cvmDriverLock(driver);
    vm = virDomainObjListFindByName(driver->domains, name);
    cvmDriverUnlock(driver);

    if (!vm) {
        virReportError(VIR_ERR_NO_DOMAIN,
                       _("no domain with matching name '%s'"), name);
        goto cleanup;
    }

    if (virDomainLookupByNameEnsureACL(conn, vm->def) < 0)
        goto cleanup;

    dom = virGetDomain(conn, vm->def->name, vm->def->uuid, vm->def->id);

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return dom;
}


static int cvmDomainIsActive(virDomainPtr dom)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr obj;
    int ret = -1;

    if (!(obj = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainIsActiveEnsureACL(dom->conn, obj->def) < 0)
        goto cleanup;

    ret = virDomainObjIsActive(obj);

 cleanup:
#if 1
    virDomainObjEndAPI(&obj);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return ret;
}


static int cvmDomainIsPersistent(virDomainPtr dom)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr obj;
    int ret = -1;

    if (!(obj = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainIsPersistentEnsureACL(dom->conn, obj->def) < 0)
        goto cleanup;

    ret = obj->persistent;

 cleanup:
#if 1
    virDomainObjEndAPI(&obj);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return ret;
}

static int cvmDomainIsUpdated(virDomainPtr dom)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr obj;
    int ret = -1;

    if (!(obj = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainIsUpdatedEnsureACL(dom->conn, obj->def) < 0)
        goto cleanup;

    ret = obj->updated;

 cleanup:
#if 1
    virDomainObjEndAPI(&obj);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return ret;
}

static int cvmConnectGetVersion(virConnectPtr conn, unsigned long *version)
{
    struct cvm_driver *driver = conn->privateData;
    struct utsname ut;
    int ret = -1;

    if (virConnectGetVersionEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);

    if (driver->cvmVersion == 0) {
        uname(&ut);

        if (virParseVersionString(ut.release, &driver->cvmVersion, true) < 0) {
            virReportError(VIR_ERR_INTERNAL_ERROR,
                           _("cannot parse version %s"), ut.release);
            goto cleanup;
        }
    }

    *version = driver->cvmVersion;
    ret = 0;

 cleanup:
    cvmDriverUnlock(driver);
    return ret;
}


static char *cvmConnectGetHostname(virConnectPtr conn)
{
    if (virConnectGetHostnameEnsureACL(conn) < 0)
        return NULL;

    return virGetHostname();
}


static int cvmConnectListDomains(virConnectPtr conn, int *ids, int nids)
{
    struct cvm_driver *driver = conn->privateData;
    int n;

    if (virConnectListDomainsEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    n = virDomainObjListGetActiveIDs(driver->domains, ids, nids,
                                     virConnectListDomainsCheckACL, conn);
    cvmDriverUnlock(driver);

    return n;
}
static int cvmConnectNumOfDomains(virConnectPtr conn)
{
    struct cvm_driver *driver = conn->privateData;
    int n;

    if (virConnectNumOfDomainsEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    n = virDomainObjListNumOfDomains(driver->domains, true,
                                     virConnectNumOfDomainsCheckACL, conn);
    cvmDriverUnlock(driver);

    return n;
}
static virDomainPtr cvmDomainCreateXML(virConnectPtr conn, const char *xml,
                                       unsigned int flags)
{
    struct cvm_driver *driver = conn->privateData;
    virDomainDefPtr def;
    virDomainObjPtr vm = NULL;
    virDomainPtr dom = NULL;
    virObjectEventPtr event = NULL;
    unsigned int parse_flags = VIR_DOMAIN_DEF_PARSE_INACTIVE;

    virCheckFlags(VIR_DOMAIN_START_AUTODESTROY |
                  VIR_DOMAIN_START_VALIDATE, NULL);

    if (flags & VIR_DOMAIN_START_VALIDATE)
        parse_flags |= VIR_DOMAIN_DEF_PARSE_VALIDATE_SCHEMA;

    virNWFilterReadLockFilterUpdates();
    cvmDriverLock(driver);
    if (!(def = virDomainDefParseString(xml, driver->caps, driver->xmlopt,
                                        NULL, parse_flags)))
        goto cleanup;


    if (virDomainCreateXMLEnsureACL(conn, def) < 0)
        goto cleanup;

    if (!(vm = virDomainObjListAdd(driver->domains, def,
                                   driver->xmlopt,
                                   VIR_DOMAIN_OBJ_LIST_ADD_LIVE |
                                   VIR_DOMAIN_OBJ_LIST_ADD_CHECK_LIVE,
                                   NULL)))
        goto cleanup;
    def = NULL;

    if (cvmStartVMDaemon(conn, driver, vm,
                         (flags & VIR_DOMAIN_START_AUTODESTROY)) < 0) {
        virDomainAuditStart(vm, "booted", false);
        if (!vm->persistent)
            virDomainObjListRemove(driver->domains, vm);
        goto cleanup;
    }
    virDomainAuditStart(vm, "booted", true);
    event = virDomainEventLifecycleNewFromObj(vm,
                                     VIR_DOMAIN_EVENT_STARTED,
                                     VIR_DOMAIN_EVENT_STARTED_BOOTED);

    dom = virGetDomain(conn, vm->def->name, vm->def->uuid, vm->def->id);

 cleanup:
    virDomainDefFree(def);
    virDomainObjEndAPI(&vm);

    virObjectEventStateQueue(driver->domainEventState, event);
    cvmDriverUnlock(driver);
    virNWFilterUnlockFilterUpdates();
    return dom;
}


static int cvmDomainShutdownFlags(virDomainPtr dom,
                                  unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    char *info = NULL;
    int ret = -1;

    virCheckFlags(0, -1);

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainShutdownFlagsEnsureACL(dom->conn, vm->def, flags) < 0)
        goto cleanup;

#if 0
    if (cvmMonitorCommand(driver, vm, "system_powerdown", &info) < 0) {
        virReportError(VIR_ERR_OPERATION_FAILED, "%s",
                       _("shutdown operation failed"));
        goto cleanup;
    }
    ret = 0;
#endif

 cleanup:
    VIR_FREE(info);
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return ret;
}

static int
cvmDomainShutdown(virDomainPtr dom)
{
    return cvmDomainShutdownFlags(dom, 0);
}

static int
cvmDomainDestroyFlags(virDomainPtr dom,
                      unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    virObjectEventPtr event = NULL;
    int ret = -1;

    virCheckFlags(0, -1);

    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        return -1;

    if (virDomainDestroyFlagsEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    cvmShutdownVMDaemon(driver, vm, VIR_DOMAIN_SHUTOFF_DESTROYED);
    virDomainAuditStop(vm, "destroyed");
    event = virDomainEventLifecycleNewFromObj(vm,
                                     VIR_DOMAIN_EVENT_STOPPED,
                                     VIR_DOMAIN_EVENT_STOPPED_DESTROYED);
    if (!vm->persistent)
        virDomainObjListRemove(driver->domains, vm);
    ret = 0;

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    virObjectEventStateQueue(driver->domainEventState, event);
    cvmDriverUnlock(driver);
    return ret;
}


static int cvmDomainDestroy(virDomainPtr dom)
{
    return cvmDomainDestroyFlags(dom, 0);
}


static char *cvmDomainGetOSType(virDomainPtr dom) {
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    char *type = NULL;

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return NULL;

    if (virDomainGetOSTypeEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

#if 1
    if (VIR_STRDUP(type, virDomainOSTypeToString(vm->def->os.type)) < 0)
        goto cleanup;
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return type;
}

/* Returns max memory in kb, 0 if error */
static unsigned long long
cvmDomainGetMaxMemory(virDomainPtr dom)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    unsigned long long ret = 0;

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainGetMaxMemoryEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

#if 1
    ret = virDomainDefGetMemoryTotal(vm->def);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
    ret = 0x10000000;
#endif

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return ret;
}

static int cvmDomainSetMaxMemory(virDomainPtr dom, unsigned long newmax)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    int ret = -1;

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainSetMaxMemoryEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (newmax < vm->def->mem.cur_balloon) {
        virReportError(VIR_ERR_INVALID_ARG, "%s",
                       _("cannot set max memory lower than current memory"));
        goto cleanup;
    }

#if 1
    virDomainDefSetMemoryTotal(vm->def, newmax);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    ret = 0;

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return ret;
}

static int cvmDomainSetMemory(virDomainPtr dom, unsigned long newmem)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    int ret = -1;

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainSetMemoryEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (virDomainObjIsActive(vm)) {
        virReportError(VIR_ERR_OPERATION_INVALID, "%s",
                       _("cannot set memory of an active domain"));
        goto cleanup;
    }

#if 1
    if (newmem > virDomainDefGetMemoryTotal(vm->def)) {
        virReportError(VIR_ERR_INVALID_ARG, "%s",
                       _("cannot set memory higher than max memory"));
        goto cleanup;
    }
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    vm->def->mem.cur_balloon = newmem;
    ret = 0;

 cleanup:
#if 1
    virDomainObjEndAPI(&vm);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    return ret;
}

static int cvmDomainGetInfo(virDomainPtr dom,
                              virDomainInfoPtr info)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    int ret = -1;

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainGetInfoEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

#if 1
    info->state = virDomainObjGetState(vm, NULL);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif


    if (!virDomainObjIsActive(vm)) {
        info->cpuTime = 0;
    } else {
        if (cvmGetProcessInfo(&(info->cpuTime), vm->pid) < 0) {
            virReportError(VIR_ERR_OPERATION_FAILED, "%s",
                           _("cannot read cputime for domain"));
            goto cleanup;
        }
    }

    info->maxMem = virDomainDefGetMemoryTotal(vm->def);
    info->memory = vm->def->mem.cur_balloon;
#if 1
    info->nrVirtCpu = virDomainDefGetVcpus(vm->def);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
    info->nrVirtCpu = 4;
#endif

    ret = 0;

 cleanup:
    virDomainObjEndAPI(&vm);
    return ret;
}


static int
cvmDomainGetState(virDomainPtr dom,
                  int *state,
                  int *reason,
                  unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    int ret = -1;

    virCheckFlags(0, -1);

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainGetStateEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

#if 1
    *state = virDomainObjGetState(vm, reason);
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    ret = 0;

 cleanup:
    virDomainObjEndAPI(&vm);
    return ret;
}


static char *cvmDomainGetXMLDesc(virDomainPtr dom,
                                 unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    char *ret = NULL;

    /* Flags checked by virDomainDefFormat */

    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainGetXMLDescEnsureACL(dom->conn, vm->def, flags) < 0)
        goto cleanup;

#if 1
    ret = virDomainDefFormat((flags & VIR_DOMAIN_XML_INACTIVE) && vm->newDef ?
                             vm->newDef : vm->def, driver->caps,
                             virDomainDefFormatConvertXMLFlags(flags));
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif


 cleanup:
    virDomainObjEndAPI(&vm);
    return ret;
}


static int cvmConnectListDefinedDomains(virConnectPtr conn,
                                        char **const names, int nnames) {
    struct cvm_driver *driver = conn->privateData;
    int n;

    if (virConnectListDefinedDomainsEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    n = virDomainObjListGetInactiveNames(driver->domains, names, nnames,
                                         virConnectListDefinedDomainsCheckACL, conn);
    cvmDriverUnlock(driver);

    return n;
}

static int cvmConnectNumOfDefinedDomains(virConnectPtr conn)
{
    struct cvm_driver *driver = conn->privateData;
    int n;

    if (virConnectNumOfDefinedDomainsEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    n = virDomainObjListNumOfDomains(driver->domains, false,
                                     virConnectNumOfDefinedDomainsCheckACL, conn);
    cvmDriverUnlock(driver);

    return n;
}


static int cvmDomainCreateWithFlags(virDomainPtr dom, unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    virObjectEventPtr event = NULL;
    int ret = -1;

    virCheckFlags(VIR_DOMAIN_START_AUTODESTROY, -1);

    virNWFilterReadLockFilterUpdates();
    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainCreateWithFlagsEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    ret = cvmStartVMDaemon(dom->conn, driver, vm,
                           (flags & VIR_DOMAIN_START_AUTODESTROY));
    virDomainAuditStart(vm, "booted", ret >= 0);
    if (ret == 0)
        event = virDomainEventLifecycleNewFromObj(vm,
                                         VIR_DOMAIN_EVENT_STARTED,
                                         VIR_DOMAIN_EVENT_STARTED_BOOTED);

 cleanup:
    virDomainObjEndAPI(&vm);
    virObjectEventStateQueue(driver->domainEventState, event);
    cvmDriverUnlock(driver);
    virNWFilterUnlockFilterUpdates();
    return ret;
}

static int cvmDomainCreate(virDomainPtr dom)
{
    return cvmDomainCreateWithFlags(dom, 0);
}

static virDomainPtr
cvmDomainDefineXMLFlags(virConnectPtr conn, const char *xml, unsigned int flags)
{
    struct cvm_driver *driver = conn->privateData;
    virDomainDefPtr def;
    virDomainObjPtr vm = NULL;
    virDomainPtr dom = NULL;
    unsigned int parse_flags = VIR_DOMAIN_DEF_PARSE_INACTIVE;

    virCheckFlags(VIR_DOMAIN_DEFINE_VALIDATE, NULL);

    if (flags & VIR_DOMAIN_DEFINE_VALIDATE)
        parse_flags |= VIR_DOMAIN_DEF_PARSE_VALIDATE_SCHEMA;

    cvmDriverLock(driver);
#if 1
    if (!(def = virDomainDefParseString(xml, driver->caps, driver->xmlopt,
                                        NULL, parse_flags)))
        goto cleanup;
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    if (virXMLCheckIllegalChars("name", def->name, "\n") < 0)
        goto cleanup;

    if (virDomainDefineXMLFlagsEnsureACL(conn, def) < 0)
        goto cleanup;

    if (!(vm = virDomainObjListAdd(driver->domains, def,
                                   driver->xmlopt,
                                   0, NULL)))
        goto cleanup;
    def = NULL;
    vm->persistent = 1;

#if 1
    if (virDomainSaveConfig(driver->configDir, driver->caps,
                            vm->newDef ? vm->newDef : vm->def) < 0) {
        virDomainObjListRemove(driver->domains, vm);
        goto cleanup;
    }
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    dom = virGetDomain(conn, vm->def->name, vm->def->uuid, vm->def->id);

 cleanup:
    virDomainDefFree(def);
    virDomainObjEndAPI(&vm);
    cvmDriverUnlock(driver);
    return dom;
}

static virDomainPtr
cvmDomainDefineXML(virConnectPtr conn, const char *xml)
{
    return cvmDomainDefineXMLFlags(conn, xml, 0);
}

static int cvmDomainUndefineFlags(virDomainPtr dom,
                                  unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    int ret = -1;

    virCheckFlags(0, -1);

    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainUndefineFlagsEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (!vm->persistent) {
        virReportError(VIR_ERR_OPERATION_INVALID, "%s",
                       _("cannot undefine transient domain"));
        goto cleanup;
    }

    if (virDomainDeleteConfig(driver->configDir, driver->autostartDir, vm) < 0)
        goto cleanup;

    if (virDomainObjIsActive(vm))
        vm->persistent = 0;
    else
        virDomainObjListRemove(driver->domains, vm);

    ret = 0;

 cleanup:
    virDomainObjEndAPI(&vm);
    cvmDriverUnlock(driver);
    return ret;
}


static int cvmDomainUndefine(virDomainPtr dom)
{
    return cvmDomainUndefineFlags(dom, 0);
}

static int cvmDomainAttachUmlDisk(struct cvm_driver *driver,
                                  virDomainObjPtr vm,
                                  virDomainDiskDefPtr disk)
{
    size_t i;
    char *cmd = NULL;
    char *reply = NULL;

    for (i = 0; i < vm->def->ndisks; i++) {
        if (STREQ(vm->def->disks[i]->dst, disk->dst)) {
            virReportError(VIR_ERR_OPERATION_FAILED,
                           _("target %s already exists"), disk->dst);
            return -1;
        }
    }

    if (!virDomainDiskGetSource(disk)) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       "%s", _("disk source path is missing"));
        goto error;
    }

    if (virAsprintf(&cmd, "config %s=%s", disk->dst,
                    virDomainDiskGetSource(disk)) < 0)
        return -1;

    if (cvmMonitorCommand(driver, vm, cmd, &reply) < 0)
        goto error;

    if (VIR_REALLOC_N(vm->def->disks, vm->def->ndisks+1) < 0)
        goto error;

    virDomainDiskInsertPreAlloced(vm->def, disk);

    VIR_FREE(reply);
    VIR_FREE(cmd);

    return 0;

 error:

    VIR_FREE(reply);
    VIR_FREE(cmd);

    return -1;
}


static int cvmDomainAttachDevice(virDomainPtr dom, const char *xml)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    virDomainDeviceDefPtr dev = NULL;
    int ret = -1;

    cvmDriverLock(driver);

    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainAttachDeviceEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (!virDomainObjIsActive(vm)) {
        virReportError(VIR_ERR_OPERATION_INVALID,
                       "%s", _("cannot attach device on inactive domain"));
        goto cleanup;
    }

    dev = virDomainDeviceDefParse(xml, vm->def, driver->caps, driver->xmlopt,
                                  VIR_DOMAIN_DEF_PARSE_INACTIVE);

    if (dev == NULL)
        goto cleanup;
#if 1
    if (dev->type == VIR_DOMAIN_DEVICE_DISK) {
        if (dev->data.disk->bus == VIR_DOMAIN_DISK_BUS_CVM) {
            ret = cvmDomainAttachUmlDisk(driver, vm, dev->data.disk);
            if (ret == 0)
                dev->data.disk = NULL;
        } else {
            virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                           _("disk bus '%s' cannot be hotplugged."),
                           virDomainDiskBusTypeToString(dev->data.disk->bus));
        }
    } else {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                       _("device type '%s' cannot be attached"),
                       virDomainDeviceTypeToString(dev->type));
        goto cleanup;
    }
#endif
 cleanup:

    virDomainDeviceDefFree(dev);
    virDomainObjEndAPI(&vm);
    cvmDriverUnlock(driver);
    return ret;
}


static int
cvmDomainAttachDeviceFlags(virDomainPtr dom,
                           const char *xml,
                           unsigned int flags)
{
    virCheckFlags(VIR_DOMAIN_AFFECT_LIVE | VIR_DOMAIN_AFFECT_CONFIG, -1);

    if (flags & VIR_DOMAIN_AFFECT_CONFIG) {
        virReportError(VIR_ERR_OPERATION_INVALID,
                       "%s", _("cannot modify the persistent configuration of a domain"));
        return -1;
    }

    return cvmDomainAttachDevice(dom, xml);
}


static int cvmDomainDetachUmlDisk(struct cvm_driver *driver,
                                  virDomainObjPtr vm,
                                  virDomainDeviceDefPtr dev)
{
    size_t i;
    int ret = -1;
    virDomainDiskDefPtr detach = NULL;
    char *cmd;
    char *reply;

    for (i = 0; i < vm->def->ndisks; i++) {
        if (STREQ(vm->def->disks[i]->dst, dev->data.disk->dst))
            break;
    }

    if (i == vm->def->ndisks) {
        virReportError(VIR_ERR_OPERATION_FAILED,
                       _("disk %s not found"), dev->data.disk->dst);
        return -1;
    }

    detach = vm->def->disks[i];

    if (virAsprintf(&cmd, "remove %s", detach->dst) < 0)
        return -1;

    if (cvmMonitorCommand(driver, vm, cmd, &reply) < 0)
        goto cleanup;

    virDomainDiskRemove(vm->def, i);

    virDomainDiskDefFree(detach);

    ret = 0;

    VIR_FREE(reply);

 cleanup:
    VIR_FREE(cmd);

    return ret;
}


static int cvmDomainDetachDevice(virDomainPtr dom, const char *xml)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    virDomainDeviceDefPtr dev = NULL;
    int ret = -1;

    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainDetachDeviceEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (!virDomainObjIsActive(vm)) {
        virReportError(VIR_ERR_OPERATION_INVALID,
                       "%s", _("cannot detach device on inactive domain"));
        goto cleanup;
    }

    dev = virDomainDeviceDefParse(xml, vm->def, driver->caps, driver->xmlopt,
                                  VIR_DOMAIN_DEF_PARSE_INACTIVE |
                                  VIR_DOMAIN_DEF_PARSE_SKIP_VALIDATE);
    if (dev == NULL)
        goto cleanup;

    if (dev->type == VIR_DOMAIN_DEVICE_DISK &&
        dev->data.disk->device == VIR_DOMAIN_DISK_DEVICE_DISK) {
        if (dev->data.disk->bus == VIR_DOMAIN_DISK_BUS_CVM)
            ret = cvmDomainDetachUmlDisk(driver, vm, dev);
        else
            virReportError(VIR_ERR_CONFIG_UNSUPPORTED, "%s",
                           _("This type of disk cannot be hot unplugged"));
    } else {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                       "%s", _("This type of device cannot be hot unplugged"));
    }

 cleanup:
    virDomainDeviceDefFree(dev);
    virDomainObjEndAPI(&vm);
    cvmDriverUnlock(driver);
    return ret;
}


static int
cvmDomainDetachDeviceFlags(virDomainPtr dom,
                           const char *xml,
                           unsigned int flags)
{
    virCheckFlags(VIR_DOMAIN_AFFECT_LIVE | VIR_DOMAIN_AFFECT_CONFIG, -1);

    if (flags & VIR_DOMAIN_AFFECT_CONFIG) {
        virReportError(VIR_ERR_OPERATION_INVALID,
                       "%s", _("cannot modify the persistent configuration of a domain"));
        return -1;
    }

    return cvmDomainDetachDevice(dom, xml);
}


static int cvmDomainGetAutostart(virDomainPtr dom,
                            int *autostart)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    int ret = -1;

    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainGetAutostartEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    *autostart = vm->autostart;
    ret = 0;

 cleanup:
    virDomainObjEndAPI(&vm);
    cvmDriverUnlock(driver);
    return ret;
}

static int cvmDomainSetAutostart(virDomainPtr dom,
                                   int autostart)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    char *configFile = NULL, *autostartLink = NULL;
    int ret = -1;

    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainSetAutostartEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (!vm->persistent) {
        virReportError(VIR_ERR_OPERATION_INVALID, "%s",
                       _("cannot set autostart for transient domain"));
        goto cleanup;
    }

    autostart = (autostart != 0);

    if (vm->autostart != autostart) {
#if 1
        if ((configFile = virDomainConfigFile(driver->configDir, vm->def->name)) == NULL)
            goto cleanup;
        if ((autostartLink = virDomainConfigFile(driver->autostartDir, vm->def->name)) == NULL)
            goto cleanup;
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

        if (autostart) {
            if (virFileMakePath(driver->autostartDir) < 0) {
                virReportSystemError(errno,
                                     _("cannot create autostart directory %s"),
                                     driver->autostartDir);
                goto cleanup;
            }

            if (symlink(configFile, autostartLink) < 0) {
                virReportSystemError(errno,
                                     _("Failed to create symlink '%s to '%s'"),
                                     autostartLink, configFile);
                goto cleanup;
            }
        } else {
            if (unlink(autostartLink) < 0 && errno != ENOENT && errno != ENOTDIR) {
                virReportSystemError(errno,
                                     _("Failed to delete symlink '%s'"),
                                     autostartLink);
                goto cleanup;
            }
        }

        vm->autostart = autostart;
    }
    ret = 0;

 cleanup:
    VIR_FREE(configFile);
    VIR_FREE(autostartLink);
    virDomainObjEndAPI(&vm);
    cvmDriverUnlock(driver);
    return ret;
}


static int
cvmDomainBlockPeek(virDomainPtr dom,
                   const char *path,
                   unsigned long long offset, size_t size,
                   void *buffer,
                   unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm;
    int fd = -1, ret = -1;
    const char *actual;

    virCheckFlags(0, -1);

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainBlockPeekEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (!path || path[0] == '\0') {
        virReportError(VIR_ERR_INVALID_ARG, "%s",
                       _("NULL or empty path"));
        goto cleanup;
    }
#if 1
    /* Check the path belongs to this domain. */
    if (!(actual = virDomainDiskPathByName(vm->def, path))) {
        virReportError(VIR_ERR_INVALID_ARG,
                       _("invalid path '%s'"), path);
        goto cleanup;
    }
#else
    printf("not implemented %d %s\n", __LINE__, __FILE__);
#endif

    path = actual;

    /* The path is correct, now try to open it and get its size. */
    fd = open(path, O_RDONLY, 0);
    if (fd == -1) {
        virReportSystemError(errno,
                             _("cannot open %s"), path);
        goto cleanup;
    }

    /* Seek and read. */
    /* NB. Because we configure with AC_SYS_LARGEFILE, off_t should
     * be 64 bits on all platforms.
     */
    if (lseek(fd, offset, SEEK_SET) == (off_t)-1 ||
        saferead(fd, buffer, size) == (ssize_t)-1) {
        virReportSystemError(errno,
                             _("cannot read %s"), path);
        goto cleanup;
    }

    ret = 0;

 cleanup:
    VIR_FORCE_CLOSE(fd);
    virDomainObjEndAPI(&vm);
    return ret;
}


static int
cvmDomainOpenConsole(virDomainPtr dom,
                     const char *dev_name,
                     virStreamPtr st,
                     unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    virDomainObjPtr vm = NULL;
    int ret = -1;
    virDomainChrDefPtr chr = NULL;
    size_t i;

    virCheckFlags(0, -1);

    cvmDriverLock(driver);
    if (!(vm = cvmDomObjFromDomainLocked(driver, dom->uuid)))
        goto cleanup;

    if (virDomainOpenConsoleEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    if (virDomainObjCheckActive(vm) < 0)
        goto cleanup;


    if (dev_name) {
        for (i = 0; i < vm->def->nconsoles; i++) {
            if (vm->def->consoles[i]->info.alias &&
                STREQ(vm->def->consoles[i]->info.alias, dev_name)) {
                chr = vm->def->consoles[i];
                break;
            }
        }
    } else {
        if (vm->def->nconsoles)
            chr = vm->def->consoles[0];
        else if (vm->def->nserials)
            chr = vm->def->serials[0];
    }

    if (!chr) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("cannot find console device '%s'"),
                       dev_name ? dev_name : _("default"));
        goto cleanup;
    }

    if (chr->source->type != VIR_DOMAIN_CHR_TYPE_PTY) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                        _("character device %s is not using a PTY"),
                       dev_name ? dev_name : NULLSTR(chr->info.alias));
        goto cleanup;
    }

#if 0
    if (virFDStreamOpenFile(st, chr->source->data.file.path,
                            0, 0, O_RDWR) < 0)
#else
    if (virFDStreamOpenFile(st, "/dev/pts/1",
                            0, 0, O_RDONLY) < 0)
#endif
        goto cleanup;

    ret = 0;
 cleanup:
    virDomainObjEndAPI(&vm);
    cvmDriverUnlock(driver);
    return ret;
}


static int
cvmConnectDomainEventRegister(virConnectPtr conn,
                              virConnectDomainEventCallback callback,
                              void *opaque,
                              virFreeCallback freecb)
{
    struct cvm_driver *driver = conn->privateData;
    int ret = 0;

    if (virConnectDomainEventRegisterEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    if (virDomainEventStateRegister(conn,
                                    driver->domainEventState,
                                    callback, opaque, freecb) < 0)
        ret = -1;
    cvmDriverUnlock(driver);

    return ret;
}

static int
cvmConnectDomainEventDeregister(virConnectPtr conn,
                                virConnectDomainEventCallback callback)
{
    struct cvm_driver *driver = conn->privateData;
    int ret = 0;

    if (virConnectDomainEventDeregisterEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    if (virDomainEventStateDeregister(conn,
                                      driver->domainEventState,
                                      callback) < 0)
        ret = -1;
    cvmDriverUnlock(driver);

    return ret;
}

static int
cvmConnectDomainEventRegisterAny(virConnectPtr conn,
                                 virDomainPtr dom,
                                 int eventID,
                                 virConnectDomainEventGenericCallback callback,
                                 void *opaque,
                                 virFreeCallback freecb)
{
    struct cvm_driver *driver = conn->privateData;
    int ret;

    if (virConnectDomainEventRegisterAnyEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    if (virDomainEventStateRegisterID(conn,
                                      driver->domainEventState,
                                      dom, eventID,
                                      callback, opaque, freecb, &ret) < 0)
        ret = -1;
    cvmDriverUnlock(driver);

    return ret;
}


static int
cvmConnectDomainEventDeregisterAny(virConnectPtr conn,
                                   int callbackID)
{
    struct cvm_driver *driver = conn->privateData;
    int ret = 0;

    if (virConnectDomainEventDeregisterAnyEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    if (virObjectEventStateDeregisterID(conn,
                                        driver->domainEventState,
                                        callbackID, true) < 0)
        ret = -1;
    cvmDriverUnlock(driver);

    return ret;
}


static int cvmConnectListAllDomains(virConnectPtr conn,
                                    virDomainPtr **domains,
                                    unsigned int flags)
{
    struct cvm_driver *driver = conn->privateData;
    int ret = -1;

    virCheckFlags(VIR_CONNECT_LIST_DOMAINS_FILTERS_ALL, -1);

    if (virConnectListAllDomainsEnsureACL(conn) < 0)
        return -1;

    cvmDriverLock(driver);
    ret = virDomainObjListExport(driver->domains, conn, domains,
                                 virConnectListAllDomainsCheckACL, flags);
    cvmDriverUnlock(driver);

    return ret;
}


static int
cvmNodeGetInfo(virConnectPtr conn,
               virNodeInfoPtr nodeinfo)
{
    if (virNodeGetInfoEnsureACL(conn) < 0)
        return -1;

    return virCapabilitiesGetNodeInfo(nodeinfo);
}


static int
cvmNodeGetCPUStats(virConnectPtr conn,
                   int cpuNum,
                   virNodeCPUStatsPtr params,
                   int *nparams,
                   unsigned int flags)
{
    if (virNodeGetCPUStatsEnsureACL(conn) < 0)
        return -1;

    return virHostCPUGetStats(cpuNum, params, nparams, flags);
}


static int
cvmNodeGetMemoryStats(virConnectPtr conn,
                      int cellNum,
                      virNodeMemoryStatsPtr params,
                      int *nparams,
                      unsigned int flags)
{
    if (virNodeGetMemoryStatsEnsureACL(conn) < 0)
        return -1;

    return virHostMemGetStats(cellNum, params, nparams, flags);
}


static int
cvmNodeGetCellsFreeMemory(virConnectPtr conn,
                          unsigned long long *freeMems,
                          int startCell,
                          int maxCells)
{
    if (virNodeGetCellsFreeMemoryEnsureACL(conn) < 0)
        return -1;

    return virHostMemGetCellsFree(freeMems, startCell, maxCells);
}


static unsigned long long
cvmNodeGetFreeMemory(virConnectPtr conn)
{
    unsigned long long freeMem;

    if (virNodeGetFreeMemoryEnsureACL(conn) < 0)
        return 0;

    if (virHostMemGetInfo(NULL, &freeMem) < 0)
        return 0;

    return freeMem;
}


static int
cvmNodeGetMemoryParameters(virConnectPtr conn,
                           virTypedParameterPtr params,
                           int *nparams,
                           unsigned int flags)
{
    if (virNodeGetMemoryParametersEnsureACL(conn) < 0)
        return -1;

    return virHostMemGetParameters(params, nparams, flags);
}


static int
cvmNodeSetMemoryParameters(virConnectPtr conn,
                           virTypedParameterPtr params,
                           int nparams,
                           unsigned int flags)
{
    if (virNodeSetMemoryParametersEnsureACL(conn) < 0)
        return -1;

    return virHostMemSetParameters(params, nparams, flags);
}


static int
cvmNodeGetCPUMap(virConnectPtr conn,
                 unsigned char **cpumap,
                 unsigned int *online,
                 unsigned int flags)
{
    if (virNodeGetCPUMapEnsureACL(conn) < 0)
        return -1;

    return virHostCPUGetMap(cpumap, online, flags);
}


static int
cvmNodeSuspendForDuration(virConnectPtr conn,
                          unsigned int target,
                          unsigned long long duration,
                          unsigned int flags)
{
#if 0
    if (virNodeSuspendForDurationEnsureACL(conn) < 0)
        return -1;

    return virNodeSuspend(target, duration, flags);
#else
    printf("not implemented %d %s\n", __LINE__, __func__);
    return 0;
#endif
}


static int
cvmNodeGetFreePages(virConnectPtr conn,
                    unsigned int npages,
                    unsigned int *pages,
                    int startCell,
                    unsigned int cellCount,
                    unsigned long long *counts,
                    unsigned int flags)
{
    virCheckFlags(0, -1);

    if (virNodeGetFreePagesEnsureACL(conn) < 0)
        return -1;

    return virHostMemGetFreePages(npages, pages, startCell, cellCount, counts);
}


static int
cvmNodeAllocPages(virConnectPtr conn,
                  unsigned int npages,
                  unsigned int *pageSizes,
                  unsigned long long *pageCounts,
                  int startCell,
                  unsigned int cellCount,
                  unsigned int flags)
{
    bool add = !(flags & VIR_NODE_ALLOC_PAGES_SET);

    virCheckFlags(VIR_NODE_ALLOC_PAGES_SET, -1);

    if (virNodeAllocPagesEnsureACL(conn) < 0)
        return -1;

    return virHostMemAllocPages(npages, pageSizes, pageCounts,
                                startCell, cellCount, add);
}


static int
cvmDomainHasManagedSaveImage(virDomainPtr dom, unsigned int flags)
{
    struct cvm_driver *driver = dom->conn->privateData;
    int ret = -1;
    virDomainObjPtr vm;

    virCheckFlags(0, -1);

    if (!(vm = cvmDomObjFromDomain(driver, dom->uuid)))
        return -1;

    if (virDomainHasManagedSaveImageEnsureACL(dom->conn, vm->def) < 0)
        goto cleanup;

    ret = 0;

 cleanup:
    virDomainObjEndAPI(&vm);
    return ret;
}


static virHypervisorDriver cvmHypervisorDriver = {
    .name = "CVM",
    .connectURIProbe = cvmConnectURIProbe,
    .connectOpen = cvmConnectOpen, /* 0.5.0 */
    .connectClose = cvmConnectClose, /* 0.5.0 */
    .connectGetType = cvmConnectGetType, /* 0.5.0 */
    .connectGetVersion = cvmConnectGetVersion, /* 0.5.0 */
    .connectGetHostname = cvmConnectGetHostname, /* 0.5.0 */
    .nodeGetInfo = cvmNodeGetInfo, /* 0.5.0 */
    .connectGetCapabilities = cvmConnectGetCapabilities, /* 0.5.0 */
    .connectListDomains = cvmConnectListDomains, /* 0.5.0 */
    .connectNumOfDomains = cvmConnectNumOfDomains, /* 0.5.0 */
    .connectListAllDomains = cvmConnectListAllDomains, /* 0.9.13 */
    .domainCreateXML = cvmDomainCreateXML, /* 0.5.0 */
    .domainLookupByID = cvmDomainLookupByID, /* 0.5.0 */
    .domainLookupByUUID = cvmDomainLookupByUUID, /* 0.5.0 */
    .domainLookupByName = cvmDomainLookupByName, /* 0.5.0 */
    .domainShutdown = cvmDomainShutdown, /* 0.5.0 */
    .domainShutdownFlags = cvmDomainShutdownFlags, /* 0.9.10 */
    .domainDestroy = cvmDomainDestroy, /* 0.5.0 */
    .domainDestroyFlags = cvmDomainDestroyFlags, /* 0.9.4 */
    .domainGetOSType = cvmDomainGetOSType, /* 0.5.0 */
    .domainGetMaxMemory = cvmDomainGetMaxMemory, /* 0.5.0 */
    .domainSetMaxMemory = cvmDomainSetMaxMemory, /* 0.5.0 */
    .domainSetMemory = cvmDomainSetMemory, /* 0.5.0 */
    .domainGetInfo = cvmDomainGetInfo, /* 0.5.0 */
    .domainGetState = cvmDomainGetState, /* 0.9.2 */
    .domainGetXMLDesc = cvmDomainGetXMLDesc, /* 0.5.0 */
    .connectListDefinedDomains = cvmConnectListDefinedDomains, /* 0.5.0 */
    .connectNumOfDefinedDomains = cvmConnectNumOfDefinedDomains, /* 0.5.0 */
    .domainCreate = cvmDomainCreate, /* 0.5.0 */
    .domainCreateWithFlags = cvmDomainCreateWithFlags, /* 0.8.2 */
    .domainDefineXML = cvmDomainDefineXML, /* 0.5.0 */
    .domainDefineXMLFlags = cvmDomainDefineXMLFlags, /* 1.2.12 */
    .domainUndefine = cvmDomainUndefine, /* 0.5.0 */
    .domainUndefineFlags = cvmDomainUndefineFlags, /* 0.9.4 */
    .domainAttachDevice = cvmDomainAttachDevice, /* 0.8.4 */
    .domainAttachDeviceFlags = cvmDomainAttachDeviceFlags, /* 0.8.4 */
    .domainDetachDevice = cvmDomainDetachDevice, /* 0.8.4 */
    .domainDetachDeviceFlags = cvmDomainDetachDeviceFlags, /* 0.8.4 */
    .domainGetAutostart = cvmDomainGetAutostart, /* 0.5.0 */
    .domainSetAutostart = cvmDomainSetAutostart, /* 0.5.0 */
    .domainBlockPeek = cvmDomainBlockPeek, /* 0.5.0 */
    .nodeGetCPUStats = cvmNodeGetCPUStats, /* 0.9.3 */
    .nodeGetMemoryStats = cvmNodeGetMemoryStats, /* 0.9.3 */
    .nodeGetCellsFreeMemory = cvmNodeGetCellsFreeMemory, /* 0.5.0 */
    .nodeGetFreeMemory = cvmNodeGetFreeMemory, /* 0.5.0 */
    .nodeGetCPUMap = cvmNodeGetCPUMap, /* 1.0.0 */
    .connectDomainEventRegister = cvmConnectDomainEventRegister, /* 0.9.4 */
    .connectDomainEventDeregister = cvmConnectDomainEventDeregister, /* 0.9.4 */
    .connectIsEncrypted = cvmConnectIsEncrypted, /* 0.7.3 */
    .connectIsSecure = cvmConnectIsSecure, /* 0.7.3 */
    .domainIsActive = cvmDomainIsActive, /* 0.7.3 */
    .domainIsPersistent = cvmDomainIsPersistent, /* 0.7.3 */
    .domainIsUpdated = cvmDomainIsUpdated, /* 0.8.6 */
    .connectDomainEventRegisterAny = cvmConnectDomainEventRegisterAny, /* 0.9.4 */
    .connectDomainEventDeregisterAny = cvmConnectDomainEventDeregisterAny, /* 0.9.4 */
    .domainOpenConsole = cvmDomainOpenConsole, /* 0.8.6 */
    .connectIsAlive = cvmConnectIsAlive, /* 0.9.8 */
    .nodeSuspendForDuration = cvmNodeSuspendForDuration, /* 0.9.8 */
    .nodeGetMemoryParameters = cvmNodeGetMemoryParameters, /* 0.10.2 */
    .nodeSetMemoryParameters = cvmNodeSetMemoryParameters, /* 0.10.2 */
    .nodeGetFreePages = cvmNodeGetFreePages, /* 1.2.6 */
    .nodeAllocPages = cvmNodeAllocPages, /* 1.2.9 */
    .domainHasManagedSaveImage = cvmDomainHasManagedSaveImage, /* 1.2.13 */
};

static virConnectDriver cvmConnectDriver = {
    .localOnly = true,
    .uriSchemes = (const char *[]){ "cvm", NULL },
    .hypervisorDriver = &cvmHypervisorDriver,
};

static virStateDriver cvmStateDriver = {
    .name = "CVM",
    .stateInitialize = cvmStateInitialize,
    .stateAutoStart = cvmStateAutoStart,
    .stateCleanup = cvmStateCleanup,
    .stateReload = cvmStateReload,
};

int cvmRegister(void)
{
    if (virRegisterConnectDriver(&cvmConnectDriver,
                                 true) < 0)
        return -1;
    if (virRegisterStateDriver(&cvmStateDriver) < 0)
        return -1;
    return 0;
}
