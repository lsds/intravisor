<!--
.. title: Version 1.0.4 released
.. slug: version-1-0-4-released
.. date: 2012-10-17 23:35:15
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Broker

 * Deal with poll() POLLIN/POLLOUT before POLL[RD]HUP to correctly handle the
   case where a client sends data and immediately closes its socket.

# Library

 * Fix memory leak with messages of QoS=2. Fixes bug #1064981.
 * Fix potential thread synchronisation problem with outgoing packets in the
   Python module. Fixes bug #1064977.

# Clients

 * Fix `mosquitto_sub -l` incorrectly only sending one message per second.
