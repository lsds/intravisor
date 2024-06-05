<!--
.. title: Mosquitto on OpenWrt
.. slug: mosquitto-on-openwrt
.. date: 2011-08-15 20:41:21
.. tags: Packaging
.. category:
.. link:
.. description:
.. type: text
-->

Thanks to work done by Karl Palsson, Mosquitto is now available on [OpenWrt],
the embedded Linux distribution frequently used on wireless routers. This is
exciting if you want a really low power way of running an MQTT broker. It also
includes the mosquitto clients and development libraries.

It's only in the source tree at the moment, so if you want to install it I
believe you'll have to download everything and compile it yourself.

Update:

Karl tells me that if you're running a binary snapshot from trunk then you can do:

```
opkg update
opkg install mosquitto mosquitto-client libmosquitto
```

You only need to build it yourself if you're running a stable binary.

[OpenWrt]: https://openwrt.org/
