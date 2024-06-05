<!--
.. title: Version 0.12 released
.. slug: version-0-12-released
.. date: 2011-07-25 22:23:19
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is an update with some features and bug fixes. The most significant
change is configuration reloading support. This will be improved to include
bridge reloading in the future.

 * Reload (most) configuration on SIGHUP.
 * Memory tracking is no longer compiled in the client library.
 * Add `--help` option to mosquitto to display usage.
 * Add `--id-prefix` option to clients to allow easier use with brokers that
   are using the `clientid_prefix` option.
 * Fix compilation on QNX.
 * Add `-P` as a synonym argument for `--pw` in the clients.
 * Fix python MosquittoMessage payload parameter. This is now returned as a
   pointer to an array of c_uint8 values so binary data is handled correctly.
   If a string is needed, use msg.payload_str
 * Fix memory leaks on client authentication.
 * If `password_file` is not defined then clients can now connect even if they 
   use a username/password.
 * Add mosquitto_reconnect() to the client library.
 * Add option for compiling with liberal protocol compliance support (enabled
   by default).
 * Fix problems with clients reconnecting and old messages remaining in the
   message store.
 * Display both ip and client id in the log message when a client connects.
 * Change the socket connection message to make it more obvious that it is just
   a socket connection being made (bug #801135).
 * Fix retained message delivery where a subscription contains a +.
 * Be more lenient when reloading persistent database to reduce errors with
   empty retained messages.
