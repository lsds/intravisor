<!--
.. title: Version 0.13 released
.. slug: version-0-13-released
.. date: 2011-09-20 23:13:16
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This release brings some new features and fixes. Although there are no real
"killer features", this release does include some fairly significant updates.
Of particular note are the fixes to subscription wildcard matching, which now
meets the spec in all cases, the Python payload parameter being a Python string
which should make life lots easier for Python developers, the non clean-session
client fixes and related persistent database fixes.

 * Implement bridge state notification messages.
 * Save client last used mid in persistent database (DB version number bumped).
 * Expose message id in Python MosquittoMessage.
 * It is now possible to set the topic QoS level for bridges.
 * Python MosquittoMessage payload parameter is now a Python string, not a
   ctypes object which makes it much easier to use.
 * Fix queueing of messages for disconnected clients. The `max_queued_messages`
   option is now obeyed.
 * C++ library is now in its own namespace, mosquittopp.
 * Add support for adding log message timestamps in the broker.
 * Fix missing mosquitto_username_pw_set() python binding.
 * Fix keepalive timeout for reconnecting non clean-session clients. Prevents
   immediate disconnection on reconnection.
 * Fix subscription wildcard matching - a subscription of +/+ will now match
   against /foo
 * Fix subscription wildcard matching - a subscription of foo/# will now match
 * against foo
 * When restoring persistent database, clients should be set to non
   clean-session or their subscriptions will be immediately removed.
 * Fix SUBACK payload for multiple topic subscriptions.
 * Don't send retained messages when a client subscribes to a topic it is
   already subscribed to.
