<!--
.. title: Version 1.3.2 released
.. slug: version-1-3-2-released
.. date: 2014-07-14 13:10:05
.. tags: Releases,Security
.. category:
.. link:
.. description:
.. type: text
-->

This is a security and bugfix release.

# Security

A bug in the way that mosquitto handles authentication plugins has been
identified. When using a plugin for authentication purposes, if the plugin
returns `MOSQ_ERR_UNKNOWN` when making an authentication check, as might happen
if a database was unavailable for example, then mosquitto incorrectly treats
this as a successful authentication. This has the potential for unauthorised
clients to access the running mosquitto broker and gain access to information
to which they are not authorised. This is an important update for users of
authentication plugins in mosquitto.

# Broker

 * Don't allow access to clients when authenticating if a security plugin
   returns an application error. Fixes bug [#1340782].
 * Ensure that bridges verify certificates by default when using TLS.
 * Fix possible crash when using pattern ACLs that do not include a %u and
   clients that connect without a username.
 * Fix subscriptions being deleted when clients subscribed to a topic beginning
   with a $ but that is not $SYS.
 * When a durable client reconnects, its queued messages are now checked
   against ACLs in case of a change in username/ACL state since it last
   connected.
 * Anonymous clients are no longer accidentally disconnected from the broker
   after a SIGHUP.
 * Fix bug [#1324411], which could have had unexpected consequences for delayed
   messages in rare circumstances.

# Client library

 * Fix topic matching edge case.
 * Fix callback deadlocks after calling `mosquitto_disconnect()`, when using
   the threaded interfaces. Closes bug [#1313725].
 * Fix SRV support when building with CMake.

# General

 * Use $(STRIP) for stripping binaries when installing, to allow easier cross
   compilation.

[#1313725]: https://bugs.launchpad.net/mosquitto/+bug/1313725
[#1324411]: https://bugs.launchpad.net/mosquitto/+bug/1324411
[#1340782]: https://bugs.launchpad.net/mosquitto/+bug/1340782
