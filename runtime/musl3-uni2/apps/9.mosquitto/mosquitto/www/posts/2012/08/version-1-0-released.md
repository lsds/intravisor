<!--
.. title: Version 1.0 released
.. slug: version-1-0-released
.. date: 2012-08-14 00:12:52
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a feature and bugfix release. This is the most significant release for
the mosquitto project so far. It encompasses &gt;20% of the total commits for
the project and has an increase in source tarball size of 95%, mostly down to
the new bundled tests and new man pages. It introduces lots of new features for
the broker and improves the API of the client libraries, although this does
mean that the libraries are incompatible with previous releases. I apologise
for this and hope you'll agree that the changes are worth it.

I've been overwhelmed with the amount of feedback that I've received recently,
thanks to everyone that has got in touch to let me know where something could
be improved. I'd particularly like to thank Nicholas Humfrey for setting me on
the continuous integration path.

On a slightly different note, my wife was expecting our first child two days
ago so it's quite likely I'll be less responsive to support requests for a
little while.

# Significant changes

These are what I think are the exciting changes for this release.

 * SSL/TLS support across the board - the broker, client libraries and pub/sub
   clients. This provides certificate based network encryption in a very
   similar manner to SSL in a web browser where the client verifies that the
   server is valid. It is also possible to use client certificates to
   authenticate the clients with the server.
 * TLS-PSK support (not on Python). This is "pre-shared-key" network encryption
   and represents a simpler encryption interface than certificate based
   encryption which makes it much more suitable for embedded/constrained
   devices.
 * The Python client library is now written in pure Python so is much easier to
   use. It supports Python 2.6, 2.7 and 3.\* (no SSL support for 2.6).
 * All client libraries have had their interface overhauled and should now be
   much saner and straightforward to use.
 * The client libraries have thread support.
 * Passwords files for the broker are stored hashed and salted and a utility
   for maintaining them has been provided.
 * It is now possible to write access and authentication plugins for the broker
   for providing custom support for authentication against e.g. a SQL database.
 * Implementation of a good test suite which has lead to improved protocol
   compliance amongst other bug fixes.
 * Masses of bug fixes.

# Downloads

Source is available on the [download page], the binary packages will follow as
soon as possible. Windows and Ubuntu packages are currently available, more to
follow.

# Changes

The complete list of changes is below:

# The broker

 * Add SSL/TLS support.
 * Add TLS-PSK support, providing a simpler encryption method for constrained
   devices.
 * Passwords are now salted+hashed if compiled with WITH_TLS (recommended).
 * Add mosquitto_passwd for handling password files.
 * Add $SYS/broker/publish/messages/{sent|received} to show the number of
   PUBLISH messages sent/received.
 * Add $SYS/broker/publish/bytes/{sent|received} to show the number of PUBLISH
   bytes sent/received.
 * Add reload parameter for security init/cleanup functions.
 * Add option for expiring disconnected persistent clients.
 * Add option for queueing of QoS 0 messages when persistent clients are
   disconnected.
 * Enforce client id limits in the broker (only when WITH_STRICT_PROTOCOL is
   defined).
 * Fix reloading of log configuration.
 * Add support for `try_private` config option for bridge connections.
 * Add support for `autosave_on_changes` config option.
 * Add support for `include_dir` config option.
 * Add support for topic remapping.
 * Usernames were being lost when a non clean-session client reconnected,
   potentially causing problems with ACLs. This has been fixed.
 * Significant improvement to memory handling on Windows.
 * Bridges with outgoing topics will now set the retain flag correctly so that
   messages will be retained on the remote broker.
 * Incoming bridge connections are now detected by checking if bit 8 of the
   protocol version number is set. This requires support from the remote
   broker.
 * Add support for `notification_topic` option.
 * Add $SYS/broker/subscriptions/count and $SYS/broker/retained messages/count.
 * Add `restart_timeout` to control the amount of time an automatic bridge will
   wait before reconnecting.
 * Overlapping subscriptions are now handled properly. Fixes bug #928538.
 * Fix reloading of `persistence_file` and `persistence_location`.
 * Fix broker crash on incorrect protocol number.
 * Fix missing COMPAT_ECONNRESET define on Windows.
 * Clients that had disconnected were not always being detected immediately on
   Linux. This has been fixed.
 * Don't save $SYS messages to the on-disk persistent db. All $SYS messages
   should be reconstructed on a restart. This means bridge connection
   notifications will now be correct on a restart.
 * Fix reloading of bridge clients from the persistent db. This means that
   outgoing bridged topics should always work.
 * Local bridges are now no longer restricted by local ACLs.
 * Discard publish messages with zero length topics.
 * Drop to "mosquitto" user even if no config file specified.
 * Don't incorrectly allow topic access if ACL patterns but no normal ACL rules
   are defined.

## The client libraries

 * Add SSL/TLS support.
 * Add TLS-PSK support, providing a simpler encryption method for constrained
   devices.
 * Add javascript/websockets client library.
 * Add `struct mosquitto *mosq` parameter for all callbacks in the client
   library. This is a binary incompatible change so the soversion of the
   libraries has been incremented. The new parameter should make it easier to
   use callbacks in practice.
 * Add `mosquitto_want_write()` for use when using own select() loop with
   `mosquitto_socket()`.
 * Add `mosquitto_connect_async()` to provide a non-blocking connect client call.
 * Add `mosquitto_user_data_set()` to allow user data pointer to be updated.
 * Add "int rc" parameter to disconnect callback to indicate whether disconnect
   was unexpected or the result of calling `mosquitto_disconnect()`.
 * Add `mosquitto_strerror()` for obtaining a string description of error numbers.
 * Add `mosquitto_connack_string()` for obtaining a string description of MQTT
   connection results.
 * Add `mosquitto_will_clear()` and change `mosquitto_will_set()` to only set the
   will.
 * Add `mosquitto_sub_topic_tokenise()` and `mosquitto_sub_topic_tokens_free()`
   utility functions to tokenise a subscription/topic string into a string
   array.
 * Add `mosquitto_topic_matches_sub()` to check whether a topic matches a
   subscription.
 * Replaced `mosquitto_log_init()` with `mosquitto_log_callback_set()` to allow
   clients to decide what to do with log messages.
 * Client will now disconnect itself from the broker if it doesn't receive a
   PINGRESP in the keepalive period after sending a PINGREQ.
 * Client will now send a PINGREQ if it has not received a message from the
   broker in keepalive seconds.
 * `mosquitto_new()` will now generate a random client id if the id parameter
   is NULL.
 * Added `max_packets` to `mosquitto_loop()`, `mosquitto_loop_read()` and
   `mosquitto_loop_write()` to control the maximum number of packets that are
   handled per call.
 * Payload parameters are now void * instead of uint8\_t \*.
 * The `clean_session` parameter has been moved from `mosquitto_connect()` to
   `mosquitto_new()` because it is a client parameter rather than a connection
   parameter.
 * Functions now use int instead of uint\*\_t where possible.
 * `mosquitto_new()` now sets errno to indicate failure type.
 * Return `MOSQ_ERR_INVAL` on zero length topic.
 * Fix automatic client id generation on Windows.
 * `mosquitto_loop_misq()` can now return `MOSQ_ERR_NO_CONN`.
 * Compile static library as well as dynamic library with default makefiles.
 * Rename C++ namespace from mosquittopp to mosqpp to remove ambiguity.
 * C++ `lib_init()`, `lib_version()` and `lib_cleanup()` are now in the mosqpp
   namespace directly, not mosquittopp class members.
 * The Python library is now written in pure Python and so no longer depends on
   libmosquitto.
 * The Python library includes SSL/TLS support.
 * The Python library should now be compatible with Python 3.

## Other

 * Fix db_dump reading of retained messages.
 * Add example of logging all messages to mysql.
 * Add C++ client example.
 * Fix potential buffer overflow in pub/sub clients.
 * Add "make binary" target that doesn't make documents.
 * Add `--help` arguments to pub/sub clients.
 * Fix building on Solaris.

[download page]: /download
