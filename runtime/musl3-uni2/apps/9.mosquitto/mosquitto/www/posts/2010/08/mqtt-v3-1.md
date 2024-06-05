<!--
.. title: MQTT v3.1
.. slug: mqtt-v3-1
.. date: 2010-08-22 00:18:19
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

The MQTT v3 spec has been updated to v3.1. The significant change is the
inclusion of the option to send a username and password as part of the connect
command. The new spec is available at
<http://www.ibm.com/developerworks/webservices/library/ws-mqtt/index.html>
and is a lot more readable and clear than the original.

Mosquitto will support the v3.1 spec in a future release, along with the
ability to control both broker and topic access by username. In the meantime,
if you need this functionality, the IBM proprietary [RSMB] broker may be
suitable for testing purposes. The RSMB package now also includes an MQTT
client library, a simple publish client and a simple subscribe client, just
like mosquitto. Be sure to check the license terms before using it!

[RSMB]: http://www.alphaworks.ibm.com/tech/rsmb
