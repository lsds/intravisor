<!--
.. title: Version 1.4.5 released
.. slug: version-1-4-5-released
.. date: 2015-11-09 22:00:57
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release:

# Broker

 * Fix possible memory leak if bridge using SSL attempts to connect to a host
   that is not up.
 * Free unused topic tree elements (fix in 1.4.3 was incomplete). Closes
   [#468987].

# Clients

 * `mosquitto_pub -l` now no longer limited to 1024 byte lines. Closes
   [#478917].

[#468987]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=468987
[#478917]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=478917
