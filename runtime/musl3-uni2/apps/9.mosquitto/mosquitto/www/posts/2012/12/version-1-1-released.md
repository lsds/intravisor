<!--
.. title: Version 1.1 released
.. slug: version-1-1-released
.. date: 2012-12-19 17:13:18
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a feature and bugfix release.

# Broker

 * Add $SYS/broker/messages/dropped
 * Add $SYS/broker/clients/expired
 * Replace $SYS/broker/+/per second/+ with moving average versions published at
   $SYS/broker/load/#
 * Add $SYS/broker/load/sockets/+ and $SYS/broker/load/connections/+
 * Documentation on password file format has been fixed.
 * Disable SSL compression. This reduces memory usage significantly and removes
   the possibility of CRIME type attacks.
 * Enable SSL_MODE_RELEASE_BUFFERS mode to reduce SSL memory usage further.
 * Add allow_duplicate_messages option.
 * ACL files can now have comment lines with # as the first character.
 * Display message on startup about which config is being loaded.
 * Fix `max_inflight_messages` and `max_queued_messages` not being applied.
 * Fix documentation error in mosquitto.conf.
 * Ensure that QoS 2 queued messages are sent out in a timely manner.
 * Local bridges now act on `clean_session` correctly.
 * Local bridges with `clean_session==false` now remove unused subscriptions on
   broker restart.
 * The $SYS/broker/heap/# messages now no longer include "bytes" as part of the
   string for ease of use.

# Client library

 * Free memory used by OpenSSL in `mosquitto_lib_cleanup()` where possible.
 * Change WebSocket subprotocol name to mqttv3.1 to make future changes easier
   and for compatibility with other implementations.
 * `mosquitto_loop_read()` and `mosquitto_loop_write()` now handle errors
   themselves rather than having `mosquitto_loop()` handle their errors. This
   makes using them in a separate event loop more straightforward.
 * Add `mosquitto_loop_forever()` / `loop_forever()` function call to make
   simple clients easier.
 * Disable SSL compression. This reduces memory usage significantly and removes
   the possibility of CRIME type attacks.
 * Enable SSL_MODE_RELEASE_BUFFERS mode to reduce SSL memory usage further.
 * `mosquitto_tls_set()` will now return an error or raise an exception
   immediately if the CA certificate or client certificate/key cannot be
   accessed.
 * Fix potential memory leaks on connection failures.
 * Don't produce return error from `mosquitto_loop()` if a system call is
   interrupted. This prevents disconnects/reconnects in threaded mode and
   simplifies non-threaded client handling.
 * Ignore SIGPIPE to prevent unnecessary client quits in threaded mode.
 * Fix document error for `mosquitto_message_retry_set()`.
 * Fix `mosquitto_topic_matches_sub()` for subscriptions with + as the final
   character. Fixes bug #1085797.
 * Rename all "obj" parameters to "userdata" for consistency with other
   libraries.
 * Reset errno before network read/write to ensure EAGAIN isn't mistakenly
   returned.
 * The message queue length is now tracked and used to determine the maximum
   number of packets to process at once. This removes the need for the
   `max_packets` parameter which is now unused.
 * Fix incorrect error value in Python `error_string()` function. Fixes bug #1086777.
 * Reset last message in/out timer in Python module when we send a PINGREQ.
   Fixes too-early disconnects.

# Clients

 * Clients now display their own version number and library version number in
   their help messages.
 * Fix `mosquitto_pub -l -q 2` disconnecting before all messages were
   transmitted.
 * Fix potential out-of-bounds array access with client ids. Fixes bug #1083182.

# Other

 * mosquitto_passwd can now convert password files with plain text files to
   hashed versions.
