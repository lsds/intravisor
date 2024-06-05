<!--
.. title: Version 0.11 released
.. slug: version-0-11-released
.. date: 2011-06-19 14:45:43
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is an update with some fairly minor changes and some bug fixes. I had
planned on more exciting features but my time has been occupied getting ready
for the 25th, when I'm getting married. Those changes will just have to wait
until 0.12!

 * Removed all old sqlite code.
 * Remove client id limit in clients.
 * Implemented $SYS/broker/heap/maximum size
 * Implemented $SYS/broker/clients/inactive to show the number of disconnected
   non-clean session clients.
 * $SYS/broker/heap/current size and maximum size messages now include "bytes"
   to match rsmb message format.
 * Implemented the `retained_persistence` config file option - a synonym of the
   `persistence` option.
 * Added security_external.c to broker source to make it easier for third
   parties to add support for their existing username/password and ACL database
   for security checks. See external_security_checks.txt.
 * $SYS messages are now only republished when their value changes.
 * Windows native broker now responds to command line arguments.
 * Simplify client disconnecting so wills gets sent in all cases (bug #792468).
 * Clients now have a `--quiet` option.
 * The on_disconnect() callback will always be called now, even if the client
   has disconnected unexpectedly.
 * Always close persistent DB file after restoring.
 * Return error code when exiting the clients.
 * mosquitto_publish() now returns `MOSQ_ERR_INVAL` if the topic contains + or
   #
 * mosquitto now silently rejects published messages with + or # in the topic.
 * `max_connections` is now a per-listener setting instead of global.
 * Connection count is now reduced when clients disconnect (bug #797983).

Thanks to Sebastian Kroll and Karl Palsson.
