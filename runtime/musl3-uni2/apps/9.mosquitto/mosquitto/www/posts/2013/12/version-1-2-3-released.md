<!--
.. title: Version 1.2.3 released
.. slug: version-1-2-3-released
.. date: 2013-12-02 23:32:55
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

In time for the second day of [Thingmonk], which I regret not being able to go
to, version 1.2.3 of mosquitto is released. This is a bugfix release.

# All components

 * Various fixes caught by [Coverity Scan].

# Broker

 * Don't always attempt to call read() for SSL clients, irrespective of whether
   they were ready to read or not. Reduces syscalls significantly.
 * Possible memory leak fixes.
 * Further fix for bug #1226040: multiple retained messages being delivered for
   subscriptions ending in #.
 * Fix bridge reconnections when using multiple bridge addresses.

# Client library

 * Fix possible memory leak in C/C++ library when communicating with a broker
   that doesn't follow the spec.
 * Block in Python `loop_stop()` until all messages are sent, as the
   documentation states should happen.
 * Fix for asynchronous connections on Windows. Closes bug #1249202.
 * Module version is now available in mosquitto.py.

# Clients

 * mosquitto_sub now uses fwrite() instead of printf() to output messages, so
   messages with NULL characters aren't truncated.

[Thingmonk]: http://redmonk.com/thingmonk/
[Coverity Scan]: https://scan.coverity.com/
