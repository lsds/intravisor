<!--
.. title: Version 1.3.1 released
.. slug: version-1-3-1-released
.. date: 2014-03-24 23:55:32
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release:

# Broker

 * Prevent possible crash on client reconnect. Closes bug #1294108.
 * Don't accept zero length unsubscription strings (MQTT v3.1.1 fix)
 * Don't accept QoS 3 (MQTT v3.1.1 fix)
 * Don't disconnect clients immediately on HUP to give chance for all data to
   be read.
 * Reject invalid un/subscriptions e.g. `foo/+bar` `#/bar`.
 * Take more care not to disconnect clients that are sending large messages.

# Client library

 * Fix socketpair code on the Mac.
 * Fix compilation for `WITH_THREADING=no`.
 * Break out of select() when calling `mosquitto_loop_stop()`.
 * Reject invalid un/subscriptions e.g. `foo/+bar` `#/bar`.

# Clients

 * Fix keepalive value on mosquitto_pub.
 * Fix possibility of mosquitto_pub not exiting after sending messages when using -l.
