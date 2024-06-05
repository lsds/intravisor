<!--
.. title: Version 0.8.2
.. slug: version-0-8-2
.. date: 2010-08-15 19:07:04
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Fix default loop() timeout value in mosquitto.py. Previous value was 0,
   causing high cpu load.
 * Fix message handling problem in client library when more than one message
   was in the client queue.
 * Fix the logic used to determine whether a QoS&gt;0 message needs to be
   retried.
 * Fix the Python sub.py example so that it quits on error.

See the [download page]. Includes Windows 32-bit binaries for the broker
compiled with Cygwin, and the client library and clients compiled natively with
Visual Studio to allow developing native Windows MQTT clients.

[download page]: /download
