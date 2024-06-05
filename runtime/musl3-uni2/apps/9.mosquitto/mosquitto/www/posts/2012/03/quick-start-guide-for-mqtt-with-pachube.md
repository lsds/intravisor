<!--
.. title: Quick start guide for MQTT with Pachube/Cosm/Xively
.. slug: quick-start-guide-for-mqtt-with-pachube
.. date: 2012-03-10 10:32:22
.. tags: Applications,Documentation,Solutions
.. category:
.. link:
.. description:
.. type: text
-->

Pachube (now Cosm) has recently announced beta support for publishing and
receiving data to their service using MQTT. This is great news and something I
know that a lot of people have been hoping for. Well done Pachube!

Their documentation is at
<https://xively.com/dev/docs/api/communicating/mqtts/> and provides enough
information to get going if you're already familiar with MQTT.

If you aren't familiar with MQTT, here's a few examples of how you can use the
new service.

First off, I'm going to use the command line MQTT clients I've created to
publish and receive data. You can get these clients as part of the [mosquitto
download].

 
# Command Line Examples

## Publishing Data

```
mosquitto_pub -h api.xively.com
              -u &lt;your xively api-key&gt;
              -t /v2/feeds/504.csv
              -m "0,29"
```

In this example we're connecting to host api.xively.com, using our xively
api-key as the username, publishing to feed /v2/feeds/504 using the csv format
and are updating datastream 0 with the value 29. Another way to achieve the
same thing would be to do:

```
mosquitto_pub -h api.xively.com
              -u &lt;your xively api-key&gt;
              -t /v2/feeds/504/datastreams/0.csv
              -m 29
```

mosquitto_pub can read data from stdin and publish it, so on Unix type systems the following arrangement is possible:

```
sensor_read | mosquitto_pub -h api.xively.com
                            -u &lt;api-key&gt;
                            -t /v2/feeds/504/datastreams/0.csv
                            -l
```

The `-l` option reads messages from stdin, sending a separate message for each
line. This means that our imaginary executable sensor_read that is reading data
from a sensor must be printing each reading as a text line.

## Retrieving Data

In the MQTT world, retrieving data is done through subscriptions:

```
mosquitto_sub -h api.xively.com
              -u &lt;api-key&gt;
              -t /v2/feeds/504/datastreams/0.csv
```

In this example, mosquitto_sub will print a text line containing the csv data
for datastream 0 of feed 504 every time it is updated.

## Last Will and Testament

The last will and testament or just "will" is a very nice feature of MQTT. When
your client connects to the MQTT broker/server, it can give the broker this
will, which consists of a topic and a message. If the client is disconnected
from the broker unexpectedly, that is to say without sending a disconnect
message, then the broker publishes the will message on the will topic.

This provides a very simple mechanism for client connection monitoring. When
your client connects it could publish a message "1" to a topic. If it also set
a will to send a message "0" to the same topic on unexpected disconnect, then
it would be possible to determine whether that client was connected by
monitoring the topic.

In the context of Xively, the same approach is possible, but using a trigger to
indicate that the client had disconnected.

The mosquitto_sub client provides support for wills as shown in the example
below:

```
mosquitto_sub -h api.xively.com
              -u &lt;api-key&gt;
              -t /v2/feeds/504/datastreams/0.csv
              --will-topic /v2/feeds/12345/datastreams/0.csv
              --will-payload "0"
```

In this example, the Xively broker would publish the value "0" to datastream 0
of feed 12345  if mosquitto_sub disconnects unexpectedly. This isn't the most
useful example because of the limitations of what mosquitto_sub provides.

# Writing Your Own Clients
In practice, to get the full benefit of the advantages that MQTT provides you
will probably want to write your own MQTT client to connect to Xively for your
specific application. The <http://mqtt.org/software> page lists client
implementations for lots of different programming languages including the
mosquitto client libraries in C/C++, libraries in Java, Python and also device
specific implementations for Arduino and other low power devices.

# MQTT Beyond Xively
The Xively offering is a slightly restricted MQTT offering. "Full" MQTT offers
a bit more scope for doing fun things using topic wildcards for example,
something that wouldn't really make sense for Xively.

There is an overview of MQTT at [mqtt man page] and examples of some
applications at <http://mosquitto.org/2012/01/do-you-use-mqtt/>.

If you'd like to play on an MQTT broker, try looking at [test.mosquitto.org].

If you want some help there are mailing lists and irc channels listed on
<http://mqtt.org/get-involved>.

[mosquitto download]: /download
[mqtt man page]: /man/mqtt-7.html
[test.mosquitto.org]: http://test.mosquitto.org/
