<!--
.. title: Version 1.4.7 released
.. slug: version-1-4-7-released
.. date: 2015-12-31 22:15:06
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release. The changes below include the changes for 1.4.6,
which wasn't announced.

# Broker

 * Add support for libwebsockets 1.6.

# Client library

 * Fix `_mosquitto_socketpair()` on Windows, reducing the chance of delays when
 * publishing. Closes [#483979].

# Clients

 * Fix `mosquitto_pub -l` stripping the final character on a line. Closes
   [#483981].

[#483979]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=483979
[#483981]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=483981
