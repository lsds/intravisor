<!--
.. title: MQTT client library
.. slug: mqtt-client-library
.. date: 2010-07-22 00:34:38
.. tags: Testing
.. category:
.. link:
.. description:
.. type: text
-->

I have been working on a client library for MQTT for the next release of
Mosquitto. It is now at a stage where it is usable and ready for wider testing.
There isn't any documentation yet (!) so it's only available in the source
repository at <http://bitbucket.org/oojah/mosquitto>. Use the "get source" link
in the top right corner of the page to  download a snapshot. If you're
interested in developing your own open source MQTT clients, it'd be great if
you could take a look to make sure the interface is sane before I make a
release!

The library itself is written in C, with bindings for C++ and Python.

I plan to package it up in a more easy to access form in the not too distant
future, hopefully with some documentation as well.

# Update
I've put the start of a man page online, which shows an example of using
libmosquitto to subscribe to a topic and print the results: [libmosquitto.3].

[libmosquitto.3]: http://mosquitto.org/man/libmosquitto-3.html
