<!--
.. title: Version 1.0.2 released
.. slug: version-1-0-2-released
.. date: 2012-08-19 06:25:35
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Broker
 * If the broker was configured for persistence, a durable client had a
   subscription to topics in $SYS/# and had messages in its queue when the
   broker restarted, then the persistent database would have messages missing
   and so the broker would not restart properly. This has been fixed.

# Library

 * Fix threading problem on some systems.

# Tests

 * Close socket after 08-ssl-connect-no-auth-wrong-ca.py test to prevent
 * subsequent tests having problems.

# Build scripts

 * Install pskfile.example in CMake. Fixes bug #1037504.

# Other

 * Fix db_dump parameter printing message store and sub chunks.
