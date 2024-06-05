<!--
.. title: Google powermeter
.. slug: google-powermeter
.. date: 2010-03-31 17:37:08
.. tags: Applications
.. category:
.. link:
.. description:
.. type: text
-->

A popular use for mqtt brokers seems to be coupling them with a [CurrentCost]
(or similar) energy monitor to then log energy data and produce pretty (and
useful!) graphs.

Google recently opened up their PowerMeter API which looks to provide very nice
graphing of energy data. They are working with utility companies directly with
in home monitors, but it's also possible to use it as an individual.

Toby Evans got to the bottom of registering a device (see his [explanatory blog
post]) which just leaves getting data to Google.

If you're already logging energy data to an MQTT broker, it's as simple as
adding another subscriber to send the data to Google. You could use the
mosquitto_sub client and a script I wrote for posting to google,
[google_powermeter_update_mqtt.pl] like so:

```
mosquitto_sub -t sensors/cc128/ch1 | google_powermeter_update_mqtt.pl
```

This assumes that the data appearing on the sensors/cc128/ch1 topic is in the
format `&lt;unix timestamp&gt; &lt;power reading in Watts&gt;`.

If you're not logging your energy data to a broker, you should probably
consider doing so :) There is another script [google_powermeter_update.pl]
which may be more suitable and can be used as:

```
google_powermeter_update.pl &lt;unix timestamp&gt; &lt;power in Watts&gt;
```

Both of the scripts need your user details adding and should be easy to modify
to match your own particular need. They also assume you're using a single
cumulative variable with your device and will need modifying if you're using
more than one variable or aren't using cumulative variables.

For reference, I use the script [cc128.pl] to read data from my CurrentCost
CC128 (Envi).

# Update:

Google has a limit of 6 API requests per hour, so the above description will
only work for a short while (the 6 request limit doesn't appear to be a hard
limit when you first exceed it, but becomes increasingly stricter). I'm now
logging my CC128 data to a mysql database and sending batch updates every 15
minutes with [google_powermeter_update_mysql.pl].

[CurrentCost]: http://currentcost.com/
[explanatory blog post]: http://2cheap2meter.blogspot.com/2010/03/setting-up-google-powermeter.html
[google_powermeter_update_mqtt.pl]: /files/perl/google_powermeter_update_mqtt.pl
[google_powermeter_update.pl]: /files/perl/google_powermeter_update.pl
[cc128.pl]: /files/perl/cc128.pl">cc128.pl
[google_powermeter_update_mysql.pl]: /files/perl/google_powermeter_update_mysql.pl
