<!--
.. title: Version 1.3 released
.. slug: version-1-3-released
.. date: 2014-03-17 00:06:32
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->


# Broker

 * The broker no longer ignores the `auth_plugin_init()` return value.
 * Accept SSLv2/SSLv3 HELLOs when using TLSv1, whilst keeping SSLv2 and SSLv3
   disabled. This increases client compatibility without sacrificing security.
 * The $SYS tree can now be disabled at runtime as well as at compile time.
 * When remapping bridged topics, only check for matches when the message
   direction is correct. This allows two identical topics to be remapped
   differently for both in and out.
 * Change `$SYS/broker/heap/current size` to `$SYS/broker/heap/current` for
   easier parsing.
 * Change `$SYS/broker/heap/maximum size` to `$SYS/broker/heap/maximum` for
   easier parsing.
 * Topics are no longer normalised from e.g `a///topic` to `a/topic`. This
   matches the behaviour as clarified by the Oasis MQTT spec. This will lead to
   unexpected behaviour if you were using topics of this form.
 * Log when outgoing messages for a client begin to drop off the end of the
   queue.
 * Bridge clients are recognised as bridges even after reloading from
   persistence.
 * Basic support for MQTT v3.1.1. This does not include being able to bridge to
   an MQTT v3.1.1 broker.
 * Username is displayed in log if present when a client connects.
 * Support for 0 length client ids (v3.1.1 only) that result in automatically
   generated client ids on the broker (see option `allow_zero_length_clientid`).
 * Ability to set the prefix of automatically generated client ids (see option
   `auto_id_prefix`).
 * Add support for TLS session resumption.
 * When using TLS, the server now chooses the cipher to use when negotiating
   with the client.
 * Weak TLS ciphers are now disabled by default.

# Client library

 * Fix support for Python 2.6, 3.0, 3.1.
 * Add support for un/subscribing to multiple topics at once in un/subscribe().
 * Clients now close their socket after sending DISCONNECT.
 * Python client now contains its version number.
 * C library `mosquitto_want_write()` now supports TLS clients.
 * Fix possible memory leak in C/C++ library when communicating with a broker
   that doesn't follow the spec.
 * Return strerror() through `mosquitto_strerror()` to make error printing
   easier.
 * Topics are no longer normalised from e.g `a///topic` to `a/topic`. This
   matches the behaviour as clarified by the Oasis MQTT spec. This will lead to
   unexpected behaviour if you were using topics of this form.
 * Add support for SRV lookups.
 * Break out of select() on publish(), subscribe() etc. when using the threaded
   interface. Fixes bug #1270062.
 * Handle incoming and outgoing messages separately. Fixes bug #1263172.
 * Don't terminate threads on `mosquitto_destroy()` when a client is not using
   the threaded interface but does use their own thread. Fixes bug #1291473.

# Clients

 * Add `--ciphers` to allow specifying which TLS ciphers to support.
 * Add support for SRV lookups.
 * Add `-N` to sub client to suppress printing of EOL after the payload.
 * Add `-T` to sub client to suppress printing of a topic hierarchy.
