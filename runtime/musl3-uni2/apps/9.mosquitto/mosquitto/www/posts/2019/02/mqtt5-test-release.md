<!--
.. title: MQTT 5 Test Release
.. slug: mqtt5-test-release
.. date: 2019-02-14 10:30:00 UTC
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

The work on MQTT v5 support in Mosquitto has reached a point where it may be of interest to a range of people. It is not yet complete, but wider testing and feedback would be appreciated.

The source is available at [mosquitto-mqtt5-test1.tar.gz] and can be compiled as normal.

## Supported features

* Session expiry
* Message expiry
* Reason code on all ACKs (not all reason codes are used)
* Reason string on all ACKs (no reason strings are provided by the broker however)
* Payload format and content type
* Request / response pattern
* Subscription ID
* Topic alias
* Flow control
* User properties
* Optional server feature availability
* Subscription options
* Server keep alive
* Assigned Client ID


## Unsupported features

* Shared subscriptions
* Extended authentication
* Server reference
* Not all reason codes are used by the broker
* Bridges do not use MQTT v5
* On disk persistence does not include MQTT 5 property support
* The broker will not create topic aliases


[mosquitto-mqtt5-test1.tar.gz]: https://mosquitto.org/files/source/test/mosquitto-mqtt5-test1.tar.gz
