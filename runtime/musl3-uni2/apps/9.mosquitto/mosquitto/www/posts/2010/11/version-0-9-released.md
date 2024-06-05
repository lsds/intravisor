<!--
.. title: Version 0.9 released
.. slug: version-0-9-released
.. date: 2010-11-15 01:04:47
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a features release. It is probably the most significant change for
mosquitto so far.

The important change is the removal of the sqlite dependency, along with the
associated pcre and sqlite3-pcre dependencies. This results in better
performance both in terms of messages handled per second and memory usage.
Optional support for importing existing persistent databases in sqlite3 format
is provided, with the option compiled in by default. This will be set to not be
compiled by default in 0.10 and then removed in 0.11.

This release also provides support for the recently updated MQTT v3.1 spec -
most notably offering username/password authentication support. The client
library and clients have full v3.1 support. The broker is fully compatible with
v3.1, but doesn't provide any mechanism for controlling username/password
control. This will come in 0.10.

One goal of mosquitto is to be a drop in replacement for the IBM rsmb broker.
Another goal is to do more than rsmb :) I'm still working on the first goal,
but this release helps with the second as mosquitto now has IPv6 support, which
isn't supported in rsmb.

A detailed list of changes is given below:

 * Client and message data is now stored in memory with custom routines rather
   than a sqlite database. This removes the dependencies on sqlite, pcre and
   sqlite3-pcre. It also means that the persistent database format has had to
   be reimplemented in a custom format. Optional support for importing old
   sqlite databases is provided.
 * Added IPv6 support for mosquitto and the clients.
 * Provide username and password support for the clients and client libraries.
   This is part of the new MQTT v3.1 spec.
 * The broker supports the username and password connection flags, but will not
   do anything with the username and password.
 * Python callback functions now optionally take an extra argument which will
   return the user object passed to the `Mosquitto()` constructor, or the calling
   python object itself if nothing was given to `Mosquitto()`.
 * Remove the mosquitto command line option `-i interface`.
 * Remove the mosquitto.conf "interface" variable.
 * Add support for the listener config variable (replaces the interface
   variable)
 * Add support for the `bind_address` config variable.
 * Change the port config variable behaviour to match that of rsmb (applies to
   the default listener only, can be given just once).
 * Fix QoS 2 protocol compliance - stop sending duplicate messages and handle
   timeouts correctly. Fixes bug #598290.
 * Set retain flag correctly for outgoing messages. It should only be set for
   messages sent in response to a subscribe command (ie. stale data).
 * Fix bug in returning correct CONNACK result to `on_connect` client callback.
 * Don't send client will if it is disconnected for exceeding its keepalive
   timer.
 * Fix client library unsubscribe function incorrectly sending a SUBSCRIBE
   command when it should be UNSUBSCRIBE.
 * Fix `max_inflight_messages` and `max_queued_messages` operation. These
   parameters now apply only to QoS 1 and 2 messages and are used regardless of
   the client connection state.
 * mosquitto.conf now installed to /etc/mosquitto/mosquitto.conf instead of
   /etc/mosquitto.conf. The /etc/mosquitto/ directory will be used for password
   and access control files in the future.
 * Give the compile time option of using 32-bit integers for the database IDs
   instead of 64-bit integers. This is useful where htobe64()/be64toh() are not
   available or for embedded systems for example.
 * The DUP bit is now set correctly when resending PUBREL messages.
 * A port to Windows native has been partially completed. This currently drops
   a number of features, including the ability to change configuration
   parameters and persistent storage.

See the [download page] for the update. Debian and Ubuntu users should note
that the package libmosquitto0-python has been renamed python-mosquitto to
comply with Debian naming policies. The Debian packages aren't yet ready.

[download page]: /download
