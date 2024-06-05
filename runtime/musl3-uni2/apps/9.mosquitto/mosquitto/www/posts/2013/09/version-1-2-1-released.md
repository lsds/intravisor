<!--
.. title: Version 1.2.1 released
.. slug: version-1-2-1-released
.. date: 2013-09-18 22:04:15
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Broker:

 * The broker no longer ignores the `auth_plugin_init()` return value. Closes
   bug #1215084.
 * Use `RTLD_GLOBAL` when opening authentication plugins on posix systems.
   Fixes resolving of symbols in libraries used by authentication plugins.
 * Add/fix some config documentation.
 * Fix ACLs for topics with $SYS.
 * Clients loaded from the persistence file on startup were not being added to
   the client hash, causing subtle problems when the client reconnected,
   including ACLs failing. This has been fixed.
 * Add note to mosquitto-tls man page stating that certificates need to be
   unique. Closes bug #1221285.
 * Fix incorrect retained message delivery when using wildcard subs in some
   circumstances. Fixes bug #1226040.

# Client library

 * Fix support for Python 2.6, 3.0, 3.1.
 * Fix TLS subjectAltName verification and segfaults.
 * Handle EAGAIN in Python on Windows. Closes bug #1220004.
 * Fix compilation when using `WITH_TLS=no`.
 * Don't fail reconnecting in Python when broker is temporarily unavailable.
