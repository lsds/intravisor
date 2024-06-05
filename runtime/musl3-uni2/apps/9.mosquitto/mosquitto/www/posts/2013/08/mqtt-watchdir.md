<!--
.. title: mqtt-watchdir
.. slug: mqtt-watchdir
.. date: 2013-08-15 20:43:13
.. tags: Misc
.. category:
.. link:
.. description:
.. type: text
-->

Recursively watch a directory for modifications and publish file content to an
MQTT broker

`mqtt-watchdir` is a Python program by [Jan-Piet Mens] to watch a directory and
publish new or modified files in that directory hierarchy to an MQTT broker,
using a matching topic. Source and instructions are available at
<https://github.com/jpmens/mqtt-watchdir> and it is also available via pypi.

It is a similar idea to my [mqttfs] fuse filesystem, but ultimately implemented
in a better (and portable) manner.

[Jan-Piet Mens]: https://twitter.com/jpmens
[mqttfs]: https://bitbucket.org/oojah/mqttfs
