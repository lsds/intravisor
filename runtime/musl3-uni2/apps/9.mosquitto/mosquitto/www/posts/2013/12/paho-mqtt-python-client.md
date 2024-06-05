<!--
.. title: Paho MQTT Python Client
.. slug: paho-mqtt-python-client
.. date: 2013-12-21 22:24:56
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

The Mosquitto Python client was donated to the Eclipse Paho project in June of
this year. As mosquitto.py has been very popular, I have been maintaining both
code bases together.

With the Mosquitto project also moving to Eclipse it is now even more redundant
to keep maintaining mosquitto.py so I would like to recommend that everybody
currently using mosquitto.py move over to using the Paho Python client.

The current state of the Paho client is now available on [pypi] and can be
installed using `pip install paho-mqtt`.

To port code from mosquitto.py, you should change:

```
import mosquitto
mqttc = mosquitto.Mosquitto()
```

to:

```
import paho.mqtt.client as paho
mqttc = paho.Client()
```

All error codes e.g. `MOSQ_ERR_SUCCESS` change to `MQTT_ERR_SUCCESS`.

The Paho module has a compatibility Mosquitto class that means a very simple
(but not recommended for the long term) port can be achieved with the following
line, assuming none of the error codes are used:

```
import paho.mqtt.client as mosquitto
```

I will keep applying updates to mosquitto.py until the Paho 1.0 release.

[pypi]: https://pypi.python.org/pypi/paho-mqtt
