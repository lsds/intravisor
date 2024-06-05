<!--
.. title: Version 0.6 released
.. slug: version-0-6-released
.. date: 2010-05-05 22:57:20
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a new features release. It offers quite a bit of change over the
previous version. More details of the new features can be found in the
[man pages].

The substantial changes are:

 * Basic support for connecting multiple MQTT brokers together (bridging).
 * mosquitto_sub can now subscribe to multiple topics (limited to a global
   QoS).
 * mosquitto_pub can now send a file as a message.
 * mosquitto_pub can now read all of stdin and send it as a message.
 * mosquitto_pub can now read stdin and send each line as a message.
 * Implement a more efficient database design, so that only one copy of each
   message is held in the database, rather than one per subscribed client.
 * Add support for automatic upgrading of the mosquitto DB from v1 to v2.
 * If a retained message is received with a zero length payload, the retained
   message for that topic is deleted.
 * Implement the `max_inflight_messages` and `max_queued_messages` features in
   the broker.

The less visible features and bug fixes are as follows:

 * Add support for disabling `clean session` for the sub client.
 * mosquitto will now correctly run VACUUM on the persistent database on exit.
 * Add the `store_cleanup_interval` config option for dealing with the internal
   message store.
 * Add `persistence_file` config option to allow changing the filename of the
   persistence database. This allows multiple mosquitto DBs to be stored in the
   same location whilst keeping `persistence_location` compatible with rsmb.
 * Don't store QoS=0 messages for disconnected clients. Fixes bug #572608. This
   wasn't correctly fixed in version 0.5.
 * Don't disconnect clients if they send a PUBLISH with zero length payload
   (bug #573610).
 * Send through zero length messages.
 * Produce a warning on unsupported rsmb options instead of quitting.
 * Describe clean session flag in the mqtt man page.

Get it from the [download page]. Windows and Ubuntu binaries will follow along
shortly.

[man pages]: /documentation
[download page]: /download
