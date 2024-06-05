<!--
.. title: Automation: Has the oven warmed up yet?
.. slug: automation-has-the-oven-warmed-up-yet
.. date: 2010-06-07 14:55:54
.. tags: Automation
.. category:
.. link:
.. description:
.. type: text
-->

In the Bang Goes the Theory episode [The Human Power Station] a family of four
people had their electricity supplied by a large group of cyclists on cycles
hooked up to generators, the point being to highlight the amount of energy that
is used and wasted on a daily basis. There's a video on [youtube].

One example that seemed to waste a lot of energy was cooking roast dinner. The
oven was turned on to preheat (this is often the first instruction in a
recipe), but it wasn't actually used until a significant time later, wasting a
lot of energy. An example which may be more common is turning the oven on to
preheat before cooking frozen food (which requires no preparation), then
forgetting to check to see if it has preheated.

This used to happen to me, but I've solved the problem by using my electricity
monitor (I have an electric oven), mqtt and asterisk.

First off, we need to monitor electricity usage. I do this with a [CurrentCost]
CC128 (note that EON customers in the UK can apply to get one of these for free
in an [Energy Fit] pack) hooked up to a low power computer that is running
mosquitto. If you're running Linux, you can use [cc128_read.py] or
[cc128_read.pl] to read the data coming from the monitor and publish it to an
mqtt broker. A second client, [cc128_parse.pl], takes the data from the monitor
and republishes it to the broker in a friendlier format - the Unix timestamp of
the reading and the power usage, separated by a single space.

To figure out when the oven has warmed up, I look at the electricity usage with
the oven heater on - approximately 2.4kW. If the energy usage drops below this
value, I know that the oven heater has turned off and so the oven has warmed
up. This is of course slightly simplistic - I'm not actually measuring the
oven, just the electricity usage so if I turned on the kettle at the same time
it could cause my guess to be incorrect. When CurrentCost produce their
individual appliance monitors, I'll be able to be certain of how much
electricity just the oven is using.

This uncertainty means that I only want to turn the oven monitor on when I've
actually turned the oven on. Looking for an easy way to start the monitor, I
spotted my house phone - a Siemens C460IP - which is a "normal" land line phone
and an IP phone all in one. I've got Asterisk running on the same server as
mosquitto, so it's an ideal solution for controlling things. Configuring
Asterisk is way beyond the scope of this text, so I'm only going to talk about
the bits I changed. I added a new extension number 100 which, when called,
starts the oven monitor:

```
exten =&gt; 100,1,Answer()
exten =&gt; 100,n,System(echo "/usr/local/bin/oven_pub.pl" | at now)
exten =&gt; 100,n,Playback(oven-trigger)
exten =&gt; 100,n,Hangup
```

This answers the call, starts the monitor, plays a sound clip so the person
calling knows what has happened and then hangs up. I'm using the "at" command
here as a simple way of putting the job into the background, thanks to [Ed] for
the suggestion. The script [oven_monitor.pl] looks for the electricity usage to
drop beneath 2kW, then runs `oven_warmed_up.sh` and exits.

The final step is to do something in [oven_warmed_up.sh] to give feedback. I
make use of asterisk once again and initiate a call to the phone - so when the
oven has warmed up I get a phone call with a message that tells me so. The
outgoing call is initiated by moving [oven.call] to
/var/spool/asterisk/outgoing/, as shown in the script.

Do you have any suggestions on how to improve this? Or other ways of using
asterisk or mqtt like this? Let me know in the comments!

[The Human Power Station]: http://www.bbc.co.uk/programmes/b00p8469
[youtube]: http://www.youtube.com/watch?v=C93cL_zDVIM
[CurrentCost]: http://www.currentcost.com/
[Energy Fit]: http://www.eon-uk.com/media/energyfit.aspx
[cc128_read.py]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/cc128_read.py
[cc128_read.pl]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/cc128_read.pl
[parse.pl]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/cc128_parse.pl
[Ed]: http://twitter.com/ribzlike
[oven_monitor.pl]: /files/examples/oven-asterisk/oven_monitor.pl
[oven_warmed_up.sh]: /files/examples/oven-asterisk/oven_warmed_up.sh
[oven.call]: /files/examples/oven-asterisk/oven.call
