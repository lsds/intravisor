<!--
.. title: Version 0.9.3 released
.. slug: version-0-9-3-released
.. date: 2011-03-11 17:08:49
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release:

 * Set retained message status for QoS 2 messages (bug #726535).
 * Only abort with an error when opening listening sockets if no address family is available, rather than aborting when any address family is not available.
 * Don't clean queued messages when a non clean session client reconnects.
 * Make mosquitto.py compatible with Python &lt;2.6.
 * Fix mosquitto.h header includes for Windows.

Please see the [download page].

Thanks to Joe B, David Monro,  Yuvraaj Kelkar and Colin Jones.

[download page]: /download
