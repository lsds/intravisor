<!--
.. title: Version 1.2.2 released
.. slug: version-1-2-2-released
.. date: 2013-10-21 23:05:04
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release:

# Broker

 * Fix compliance with `max_inflight_messages` when a non-clean session client
   reconnects. Closes one of the issues on bug #1237389.

# Client library

 * Fix incorrect inflight message accounting, which caused messages to go
 * unsent. Partial fix for bug #1237351.
 * Fix potential memory corruption when sending QoS&gt;0 messages at a high
   rate using the threaded interface. Further fix for #1237351.
 * Fix incorrect delay scaling when exponential_backoff=true in
   mosquitto_reconnect_delay_set().
 * Some pep8 fixes for Python.
