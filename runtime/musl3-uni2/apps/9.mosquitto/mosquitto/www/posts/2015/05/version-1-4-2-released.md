<!--
.. title: Version 1.4.2 released
.. slug: version-1-4-2-released
.. date: 2015-05-07 22:58:11
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Broker

 * Fix bridge prefixes only working for the first outgoing message. Closes [#464437].
 * Fix incorrect bridge connection notifications on local broker.
 * Fix persistent db writing on Windows. Closes [#464779].
 * ACLs are now checked before sending a will message.
 * Fix possible crash when using bridges on Windows. Closes [#465384].
 * Fix parsing of `auth_opt_` arguments with extra spaces/tabs.
 * Broker will return CONNACK rc=5 when a username/password is not authorised.
   This was being incorrectly set as rc=4.
 * Fix handling of payload lengths&gt;4096 with websockets.

# Client library

 * Inflight message count wasn't being decreased for outgoing messages using
   QoS 2, meaning that only up to 20 QoS 2 messages could be sent. This has
   been fixed. Closes [#464436].
 * Fix CMake dependencies for C++ wrapper building. Closes [#463884].
 * Fix possibility of select() being called with a socket that is
   &gt;FD_SETSIZE. This is a fix for [#464632].
 * Fix calls to `mosquitto_connect*_async()` not completing.

[#464437]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=464437
[#464779]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=464779
[#465384]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=465384
[#463884]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=463884
[#464436]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=464436
[#464632]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=464632
