<!--
.. title: Version 0.4 released
.. slug: version-0-4-released
.. date: 2010-01-05 10:54:37
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

 * Added support for wildcard subscriptions using + and #.
 * All network operations are now non-blocking and can cope with partial packets, meaning that networking should be a lot more reliable.
 * Total messsages/bytes sent/received are now available in $SYS.
 * Improved logging information - use client ip address and id instead of socket number.
 * Keepalive==0 is now correctly treated as "never disconnect".
 * Default logging destination no longer includes "topics" to prevent possible error logging to the db before it is initialised.
 * Periodic $SYS messages can now be disabled.

See the [changelog] for full details.

[changelog]: /ChangeLog.txt
