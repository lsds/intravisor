<!--
.. title: Version 0.14 released
.. slug: version-0-14-released
.. date: 2011-11-16 23:23:03
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a fairly minor feature release. The major changes are the pattern
matching ACL support, the support for running directly as a Windows service and
the change to the network code to attempt to send packets immediately. The
Windows binary is now supplied as an installer rather than a zip file.

 * Add support for matching ACLs based on client id and username.
 * Add a Windows installer file (NSIS based).
 * Add native support for running the broker as a Windows service. This is the
   default when installed using the new installer.
 * Fix client count for listeners. When clients disconnect, decrement the
   count. Allow `max_connections` to work again.
 * Attempt to send all packets immediately upon being queued. This will result
   in more immediate network communication in many cases.
 * Log IP address when reporting CONNACK packets if the client id isn't yet
   known.
 * Fix payload length calculation in python `will_set` function.
 * Fix Python publish and `will_set` functions for payload=None.
 * Fix keepalive value being lost when reconnecting a client (bug #880863).
 * Persistence file writing now uses portable file functions, so the Cygwin
   broker build should no longer be necessary.
 * Duplicate code between the client and broker side has been reduced.
 * Queued messages for clients reconnecting with `clean_session=false` set were
   not being sent until the next message for that client was received. This has
   been fixed (bug #890724).
 * Fix subscriptions to # incorrectly matching against topics beginning with /
