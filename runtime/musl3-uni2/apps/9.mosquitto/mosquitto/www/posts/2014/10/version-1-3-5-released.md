<!--
.. title: Version 1.3.5 released
.. slug: version-1-3-5-released
.. date: 2014-10-08 23:23:22
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Broker

 * Fix possible memory leak when using a topic that has a leading slash. Fixes
   bug #1360985.
 * Fix saving persistent database on Windows.
 * Temporarily disable ACL checks on subscriptions when using MQTT v3.1.1. This
   is due to the complexity of checking wildcard ACLs against wildcard
   subscriptions. This does not have a negative impact on security because
   checks are still made before a message is sent to a client. Fixes bug
   #1374291.
 * When using -v and the broker receives a SIGHUP, verbose logging was being
   disabled. This has been fixed.

# Client library

 * Fix mutex being incorrectly passed by value. Fixes bug #1373785.
