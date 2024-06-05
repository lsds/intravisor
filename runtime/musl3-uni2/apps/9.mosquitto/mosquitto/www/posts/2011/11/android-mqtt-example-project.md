<!--
.. title: Android MQTT example project
.. slug: android-mqtt-example-project
.. date: 2011-11-03 14:54:30
.. tags: Mobile
.. category:
.. link:
.. description:
.. type: text
-->

To celebrate the news that the IBM Java MQTT client implementation will be
released as open source, I've put together a simple Android example based on
the [MQTT service code written by Dale Lane]. I'm a beginner at both Java and
Android, so expect it to be a bit rough.

The example displays incoming payload text on a text label. It's a complete
project that you can build and install on your phone with only a few small
changes - search for "CHANGE ME" in
src/org/mosquitto/android/mqtt/MQTTDemo.java.

To get the project working, assuming you've already installed the android sdk,
first get the IBM Java library (see <http://mqtt.org/software>) and put it in
&lt;project dir&gt;/lib then do the following:

```
android update project -p &lt;path to project&gt;
# If the update complains about build.xml - delete it and run again
cd &lt;path to project&gt;
ant debug
sudo adb start-server
ant installd
```

I'll not be at all surprised if there are problems in the project due to
different sdk or tool versions. Please comment if you find a problem.

The project is available from
<http://mosquitto.org/files/examples/android-mqtt-example.zip>. Until the IBM
Java implementation is open source please be aware of the licence attached to
it.

Thanks to Dale for the core Android MQTT service implementation.

[MQTT service code written by Dale Lane]: http://dalelane.co.uk/blog/?p=1599
