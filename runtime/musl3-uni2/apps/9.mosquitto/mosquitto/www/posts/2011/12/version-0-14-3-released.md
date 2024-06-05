<!--
.. title: Version 0.14.3 released
.. slug: version-0-14-3-released
.. date: 2011-12-10 18:32:33
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Fix potential crash when client connects with an invalid CONNECT packet.
 * Fix incorrect invalid socket comparison on Windows.
 * Server shouldn't crash when a message is published to foo/ when a
   subscription to foo/# exists (bug #901697).
 * SO_REUSEADDR doesn't work the same on Windows, so don't use it.
 * Cygwin builds now support Windows service features.
 * Fix $SYS/broker/bytes/sent reporting.
