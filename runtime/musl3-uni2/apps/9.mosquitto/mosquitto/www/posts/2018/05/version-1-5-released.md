<!--
.. title: Version 1.5 released
.. slug: version-1-5-released
.. date: 2018-05-02 23:56:38 UTC+01:00
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

1.5 - 20180502
==============

This is a features release. Updated binaries will be available shortly.

# Security

 *  Fix memory leak that could be caused by a malicious CONNECT packet. This
    does not yet have a CVE assigned. Closes #533493 (on Eclipse bugtracker)

# Broker features

 * Add `per_listener_settings` to allow authentication and access control to be
   per listener.
 * Add limited support for reloading listener settings. This allows settings
   for an already defined listener to be reloaded, but port numbers must not be
   changed.
 * Add ability to deny access to SUBSCRIBE messages as well as the current
   read/write accesses. Currently for auth plugins only.
 * Reduce calls to malloc through the use of UHPA.
 * Outgoing messages with QoS>1 are no longer retried after a timeout period.
   Messages will be retried when a client reconnects.  This change in behaviour
   can be justified by considering when the timeout may have occurred.
   * If a connection is unreliable and has dropped, but without one end
    noticing, the messages will be retried on reconnection. Sending
    additional PUBLISH or PUBREL would not have changed anything.
   * If a client is overloaded/unable to respond/has a slow connection then
    sending additional PUBLISH or PUBREL would not help the client catch
    up. Once the backlog has cleared the client will respond. If it is not
    able to catch up, sending additional duplicates would not help either.
 * Add `use_subject_as_username` option for certificate based client
   authentication to use the entire certificate subject as a username, rather
   than just the CN. Closes #469467.
 * Change sys tree printing output. This format shouldn't be relied upon and
   may change at any time. Closes #470246.
 * Minimum supported libwebsockets version is now 1.3.
 * Add systemd startup notification and services. Closes #471053.
 * Reduce unnecessary malloc and memcpy when receiving a message and storing
   it. Closes #470258.
 * Support for Windows XP has been dropped.
 * Bridge connections now default to using MQTT v3.1.1.
 * `mosquitto_db_dump` tool can now output some stats on clients.
 * Perform utf-8 validation on incoming will, subscription and unsubscription
   topics.
 * new $SYS/broker/store/messages/count (deprecates $SYS/broker/messages/stored)
 * new $SYS/broker/store/messages/bytes
 * `max_queued_bytes` feature to limit queues by real size rather than
   than just message count. Closes Eclipse #452919 or Github #100
 * Add support for bridges to be configured to only send notifications to the
   local broker.
 * Add `set_tcp_nodelay` option to allow Nagle's algorithm to be disabled on
   client sockets. Closes #433.
 * The behaviour of `allow_anonymous` has changed. In the old behaviour, the
   default if not set was to allow anonymous access. The new behaviour is to
   default is to allow anonymous access unless another security option is set.
   For example, if `password_file` is set and `allow_anonymous` is not set,
   then anonymous access will be denied. It is still possible to allow
   anonymous access by setting it explicitly.

# Broker fixes
 * Fix UNSUBSCRIBE with no topic is accepted on MQTT 3.1.1. Closes #665.
 * Produce an error if two bridges share the same `local_clientid`.
 * Miscellaneous fixes on Windows.
 * `queue_qos0_messages` was not observing `max_queued_**` limits
 * When using the `include_dir` configuration option sort the files
   alphabetically before loading them.  Closes #17.
 * IPv6 is no longer disabled for websockets listeners.
 * Remove all build timestamp information including $SYS/broker/timestamp.
   Closes #651.
 * Correctly handle incoming strings that contain a NULL byte. Closes #693.
 * Use constant time memcmp for password comparisons.
 * Fix incorrect PSK key being used if it had leading zeroes.
 * Fix memory leak if a client provided a username/password for a listener with
   `use_identity_as_username` configured.
 * Fix `use_identity_as_username` not working on websockets clients.
 * Don't crash if an auth plugin returns `MOSQ_ERR_AUTH` for a username check on
   a websockets client. Closes #490.
 * Fix 08-ssl-bridge.py test when using async dns lookups. Closes #507.
 * Lines in the config file are no longer limited to 1024 characters long.
   Closes #652.
 * Fix $SYS counters of messages and bytes sent when message is sent over
   a Websockets. Closes #250.
 * Fix `upgrade_outgoing_qos` for retained message. Closes #534.
 * Fix CONNACK message not being sent for unauthorised connect on websockets.
   Closes #8.
 * Maximum connections on Windows increased to 2048.
 * When a client with an in-use client-id connects, if the old client has a
   will, send the will message. Closes #26.
 * Fix parsing of configuration options that end with a space. Closes #804.

# Client library features
 * Outgoing messages with QoS>1 are no longer retried after a timeout period.
   Messages will be retried when a client reconnects.
 * DNS-SRV support is now disabled by default.
 * Add `mosquitto_subscribe_simple()` This is a helper function to make
   retrieving messages from a broker very straightforward. Examples of its use
   are in `examples/subscribe_simple`.
 * Add `mosquitto_subscribe_callback()` This is a helper function to make
   processing messages from a broker very straightforward. An example of its use
   is in `examples/subscribe_simple`.
 * Connections now default to using MQTT v3.1.1.
 * Add `mosquitto_validate_utf8()` to check whether a string is valid UTF-8
   according to the UTF-8 spec and to the additional restrictions imposed by
   the MQTT spec.
 * Topic inputs are checked for UTF-8 validity.
 * Add `mosquitto_userdata` function to allow retrieving the client userdata
   member variable. Closes #111.
 * Add `mosquitto_pub_topic_check2()`, `mosquitto_sub_topic_check2()`, and
   `mosquitto_topic_matches_sub2()` which are identical to the similarly named
   functions but also take length arguments.
 * Add `mosquitto_connect_with_flags_callback_set()`, which allows a second
   connect callback to be used which also exposes the connect flags parameter.
   Closes #738 and #128.
 * Add `MOSQ_OPT_SSL_CTX` option to allow a user specified `SSL_CTX` to be used
   instead of the one generated by libmosquitto. This allows greater control
   over what options can be set. Closes #715.
 * Add `MOSQ_OPT_SSL_CTX_WITH_DEFAULTS` to work with `MOSQ_OPT_SSL_CTX` and have
   the default libmosquitto `SSL_CTX` configuration applied to the user provided
   `SSL_CTX`. Closes #567.

# Client library fixes
 * Fix incorrect PSK key being used if it had leading zeroes.
 * Initialise "result" variable as soon as possible in
   `mosquitto_topic_matches_sub`. Closes #654.
 * No need to close socket again if setting non-blocking failed. Closes #649.
 * Fix `mosquitto_topic_matches_sub()` not correctly matching foo/bar against
   foo/+/#. Closes #670.
 * SNI host support added.

# Client features
 * Add -F to `mosquitto_sub` to allow the user to choose the output format.
 * Add -U to `mosquitto_sub` for unsubscribing from topics.
 * Add -c (clean session) to `mosquitto_pub`.
 * Add --retained-only to `mosquitto_sub` to exit after receiving all retained
  messages.
 * Add -W to allow `mosquitto_sub` to stop processing incoming messages after a
  timeout.
 * Connections now default to using MQTT v3.1.1.
 * Default to using port 8883 when using TLS.
 * `mosquitto_sub` doesn't continue to keep connecting if CONNACK tells it the
  connection was refused.

# Client fixes
 * Correctly handle empty files with `mosquitto_pub -l`. Closes #676.

# Build
 * Add `WITH_STRIP` option (defaulting to "no") that when set to "yes" will strip
   executables and shared libraries when installing.
 * Add `WITH_STATIC_LIBRARIES` (defaulting to "no") that when set to "yes" will
   build and install static versions of the client libraries.
 * Don't run TLS-PSK tests if TLS-PSK disabled at compile time. Closes #636.
 * Support for openssl versions 1.0.0 and 1.0.1 has been removed as these are
   no longer supported by openssl.

# Documentation
 * Replace mentions of deprecated `c_rehash` with `openssl rehash`.
