<!--
.. title: MQTT on Nanode
.. slug: mqtt-on-nanode
.. date: 2011-12-31 11:07:48
.. tags: Solutions
.. category:
.. link:
.. description:
.. type: text
-->

[Nanode], the popular arduino-with-ethernet board started early in 2011 is
ideal for small MQTT based projects but has so far lacked an implementation of
MQTT.

Nick O'Leary, the author of the original Arduino MQTT client, [has created a
Nanode implementation], but it [isn't quite ready for the public].

Nicholas Humfrey has made public some code at
<https://github.com/njh/NanodeMQTT> that he says [still needs some work] but
supports publishing QoS 0 messages of up to 127 bytes long and subscribing to
topics with QoS 0.

[Nanode]: http://nanode.eu/
[has created a Nanode implementation]: https://twitter.com/#!/knolleary/status/151057575775965184
[isn't quite ready for the public]: https://twitter.com/#!/knolleary/status/151059089881960448
[still needs some work]: https://twitter.com/#!/njh/status/152913104446038018
