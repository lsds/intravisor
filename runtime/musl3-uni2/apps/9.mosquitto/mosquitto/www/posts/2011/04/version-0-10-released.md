<!--
.. title: Version 0.10 released
.. slug: version-0-10-released
.. date: 2011-04-29 19:05:28
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This release brings the new MQTT v3.1 features to the broker - client
authentication and topic access control. See [mosquitto.conf(5)] or the
included example password and ACL files.

 * Implement support for the `password_file` option and accompanying
   authentication requirements in the broker.
 * Implement topic Access Control Lists.
 * `mosquitto_will_set()` and `mosquitto_publish()` now return
   `MOSQ_ERR_PAYLOAD_SIZE` if the payload is too large (&gt;268,435,455 bytes).
 * Bridge support can now be disabled at compile time.
 * Group together network writes for outgoing packets - don't send single byte
   writes!
 * Add support for `clientid_prefixes` variable.
 * Add support for the `clientid` config variable for controlling bridge client
   ids.
 * Remove 32-bit database ID support because htobe64() no longer used.
 * Multiple client subscriptions to the same topic result in only a single
   subscription. Bug #744077.

Please see the [download page].

Thanks to Adam Rudd, Joshua Lock,  Sang Kyeong Nam and Yuvraaj Kelkar.

[mosquitto.conf(5)]: /man/mosquitto-conf-5.html
[download page]: /download
