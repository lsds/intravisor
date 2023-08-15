/*
 * remote_daemon.c: daemon start of day, guest process & i/o management
 *
 * Copyright (C) 2006-2018 Red Hat, Inc.
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
 * Author: Daniel P. Berrange <berrange@redhat.com>
 */

#include <config.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <getopt.h>
#include <grp.h>

#include "libvirt_internal.h"
#include "virerror.h"
#include "virfile.h"
#include "virlog.h"
#include "virpidfile.h"
#include "virprocess.h"

#define VIR_FROM_THIS VIR_FROM_QEMU

#include "remote_daemon.h"
#include "remote_daemon_config.h"

#include "admin/admin_server_dispatch.h"
#include "viruuid.h"
#include "remote_driver.h"
#include "viralloc.h"
#include "virconf.h"
#include "virnetlink.h"
#include "virnetdaemon.h"
#include "remote_daemon_dispatch.h"
#include "virhook.h"
#include "viraudit.h"
#include "virstring.h"
#include "locking/lock_manager.h"
#include "viraccessmanager.h"
#include "virutil.h"
#include "virgettext.h"
#include "util/virnetdevopenvswitch.h"

#include "driver.h"

#include "configmake.h"

#include "virdbus.h"

int libvirt_main(int argc, char **argv) {
    // Initialize libvirt
    if (virInitialize() < 0) {
        fprintf(stderr, "Failed to initialize libvirt\n");
        return 1;
    }


    if (virDriverLoadModule("uml", "umlRegister", false) < 0)
        return -1;


    return 0;
}