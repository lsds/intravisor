<!--
.. title: Version 0.7 released
.. slug: version-0-7-released
.. date: 2010-06-15 23:38:52
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a new features release. Note that although the number of changes is
relatively small, there is a fairly major change in the network socket handling
(to allow &gt;1024 clients) , which is one reason this has been treated as a
separate release.

Changes:

 * Use poll() instead of select() to allow &gt;1024 clients.
 * Implement `max_connections`.
 * Run VACUUM on in-memory database on receiving SIGUSR2.
 * mosquitto_pub can now send null (zero length) messages.
 * Add option to print debug messages in pub and sub clients.
 * hg revision is now exported via $SYS/broker/changeset
 * Add compile time option to disable heap memory tracking.

Bug fixes:

 * Don't store QoS=0 messages for disconnected clients with subscriptions of QoS&gt;0.
 * accept() all available sockets when new clients are connecting, rather than just one (performance advantage)
 * Send Will when client exceeds keepalive timer and is disconnected.
 * Check to see if a client has a will before sending it.
 * Correctly deal with clients connecting with the same id multiple times.
 * Fix bridge keepalive timeouts and reconnects.
 * Don't attempt to drop root privileges when running on Windows as this isn't well supported (bug #586231).

Source downloads are available at the [download page] Links for binary packages
on Ubuntu and Fedora can be found on the same page.

[download page]: /download
