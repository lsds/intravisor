<!--
.. title: Version 0.9.2 released
.. slug: version-0-9-2-released
.. date: 2011-02-10 00:28:23
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release:

 * Only send a single DISCONNECT command when using -l in the pub client.
 * Set QoS=1 on PUBREL commands to meet protocol spec.
 * Don't leak sockets on connection failure in the library.
 * Install man pages when building under cmake.
 * Fix crash bug on malformed CONNECT message.
 * Clients are now rejected if their socket peer name cannot be obtained on
   connection.
 * Fix a number of potential problems caused when a client with a duplicate id
   connects.
 * Install mosquitto.conf under cmake.

Thanks to Mark Hindess, Joshua Lock, Adam Rudd and Ben Davenport for their
help.

The source code is available as always on the [download page]. Binaries will
appear shortly.

[download page]: /download
