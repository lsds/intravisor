<!--
.. title: Challenge: Web based MQTT graphing
.. slug: challenge-web-based-mqtt-graphing
.. date: 2012-01-16 12:21:06
.. tags: Solutions
.. category:
.. link:
.. description:
.. type: text
-->

Thanks to a data feed courtesy of an IBM broker, [test.mosquitto.org] now
publishes information on energy generation and demand in the UK (in the energy/
topic tree). I think this could be used as a great demonstration for coupling
MQTT and the web.

# The challenge
Create a web based report that takes energy data from the broker over MQTT and
displays it in interesting and useful ways. Alternatively, an Android/iPhone
app would be ok, but web based is the preferred option.

# The rules
There are no rules really. Having said that, I'd be most pleased if the end
result was something that other people could learn from. There are bonus points
for solutions that work where a web proxy is the only internet access. If you
want to use new or unusual technologies that's fine.

# The prize
I'm afraid there is no tangible prize - I hope you'll be content with your work
being shown here and the respect of your peers.

# Some suggestions
Google charts is definitely worth looking at for generating the actual graphs.
Some examples of what you might show are:

 * Pie chart of generation source
 * Gauge of current mains frequency
 * Historical graph of electricity export amount

I look forward to any and all responses!

[test.mosquitto.org]: http://test.mosquitto.org/
