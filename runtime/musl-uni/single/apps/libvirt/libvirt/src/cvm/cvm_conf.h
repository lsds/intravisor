/*
 * cvm_conf.h: VM configuration management
 *
 * Copyright (C) 2006, 2007, 2010 Red Hat, Inc.
 * Copyright (C) 2006 Daniel P. Berrange
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

#ifndef __CVM_CONF_H
# define __CVM_CONF_H

# include "internal.h"
# include "libvirt_internal.h"
# include "capabilities.h"
# include "network_conf.h"
# include "virdomainobjlist.h"
# include "domain_event.h"
# include "virerror.h"
# include "virthread.h"
# include "vircommand.h"
# include "virhash.h"

# define cvmDebug(fmt, ...) do {} while (0)

# define CVM_CPUMASK_LEN CPU_SETSIZE

# define CVM_MAX_CHAR_DEVICE 16

/* Main driver state */
struct cvm_driver {
    virMutex lock;

    bool privileged;
    virStateInhibitCallback inhibitCallback;
    void *inhibitOpaque;

    unsigned long cvmVersion;
    int nextvmid;

    virDomainObjListPtr domains;
    size_t nactive;

    char *configDir;
    char *autostartDir;
    char *logDir;
    char *monitorDir;

    int inotifyFD;
    int inotifyWatch;

    virCapsPtr caps;
    virDomainXMLOptionPtr xmlopt;

    /* Event handling */
    virObjectEventStatePtr domainEventState;

    /* Mapping of 'char *uuidstr' -> virConnectPtr
     * of guests which will be automatically killed
     * when the virConnectPtr is closed*/
    virHashTablePtr autodestroy;
};

virCapsPtr  cvmCapsInit               (void);

virCommandPtr cvmBuildCommandLine(virConnectPtr conn,
                                  struct cvm_driver *driver,
                                  virDomainObjPtr dom);

#endif /* __CVM_CONF_H */
