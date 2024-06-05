<!--
.. title: Google Powermeter : Step by step
.. slug: google-powermeter-step-by-step
.. date: 2010-06-15 14:34:50
.. tags: cc128,currentcost,google,mysql,powermeter,Applications
.. category:
.. link:
.. description:
.. type: text
-->

# Note: Google Powermeter is now defunct but this post will remain here for those interested.

This is a follow up to my previous [post on using Google Powermeter],
but this time I'm going to give a step by step guide to getting your data
uploaded. The only assumptions are that you have a CurrentCost monitor (note
that CurrentCost monitors are often rebadged by electricity suppliers such as
EON in the UK so check yours) and have already connected it to your computer,
want to use MQTT and that you're using Linux, or another Unix operating system.

# Retrieving the data

The first step is to get the data from the CurrentCost into the MQTT broker.
This is straightforward - simply read data from the serial port and send it all
to the broker. I have scripts to do this with mosquitto in both [perl] and
[python].

The data coming from the CurrentCost is in XML format and as well as providing
the real time power reading every 6 seconds, will also send historical data
periodically. I'm only going to deal with the real time readings here. The next
step is to reprocess the incoming data into something more manageable, then
republish it. An example of doing that is the script [cc128_parse.pl], which
assumes you're only using the main channel from the CurrentCost. If you have
multiple monitoring channels, you'll need to modify it to suit.

# Logging the data

Google limits the number of times we can send data to 6 per hour, so we have to
log the data and then send amalgamated updates. I use mysql for this - I'm
going to assume that you've got it installed and running. Log into the mysql
console using "mysql -u root",  "mysql -u root -p" if you know the password, or
possibly "sudo mysql". We're now going to create a database and table to hold
the powermeter data, then add a user to access and update the data.

To create the database and table enter the following:

```
CREATE DATABASE powermeter;
USE 'powermeter';
CREATE TABLE powermeter (
  `id` INT NOT NULL auto_increment,
  `timestamp` INT NOT NULL,
  `temperature` FLOAT NOT NULL DEFAULT 0.0,
  `ch1` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `timestamp` (`timestamp`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;</pre>
```

Note that there's a column there for the temperature as well.

To add the user and grant access to the database:

```
CREATE USER 'powermeter'@'localhost' IDENTIFIED BY '&lt;your password&gt;';
GRANT ALL ON powermeter.* to 'powermeter'@'localhost';
```

Finally, you'll need to get data into this database. My script
[cc128_log_mysql.pl] subscribes to the data from cc128_parse.pl and logs it
into the database.  You'll need to edit it to have the correct database
details.

If you already have your power data published to an MQTT topic, it's quite
likely that you won't have it in the same format that I use above. If this is
the case, you will need to modify cc128_log_mysql.pl. Assuming your data coming
in over MQTT is just the power reading, then you can replace this:

```
@vals = split(/,/, $line);
$timestamp = @vals[0];
$temperature = @vals[1];
$ch1 = @vals[2];
```

with this:

```
$timestamp = time();
$temperature = 0;
$ch1 = $line;
```

You can of course leave the temperature column out completely if you prefer.

# Registering with Google Powermeter

Before you can send any data to Google, you need to register your device with
them. This would normally be done automatically by your device, but because
we're doing things ourselves we need to do it manually. See [2cheap2meter] and
the links it provides for more details.

We first need to decide on a few parameters for our device:

 * Manufacturer (e.g. CurrentCost)
 * Device model (e.g. CC128 or Envi)
 * Device id (e.g. Serial number or your own made up string, 1234)
 * Number of channels to log (e.g. 1)

We can then construct an address which you will paste into your web browser:

```
https://www.google.com/powermeter/device/activate?mfg=CurrentCost&amp;model=CC128&amp;did=1234&amp;dvars=1
```

`dvars` here is the number of channels (or monitors) that we wish to register.
If you have more than one channel logging, change the number accordingly - bear
in mind that you'll have to modify just about everything else in this post to
match. You will need to remember the values you put here for later.

Visiting that link will take you to the activation page, which you should
complete. After you have done this, you will be presented with authorisation
information for your new device. The piece of information we need is the 32
character string contained between "token=" and "&amp;path" (the authorisation
token) as well as the 20 digit number after "&amp;path=/user/" (your google
powermeter id).

# Sending the data

I have a script [google_powermeter_update.pl] that will query the database for
readings from the past 15 minutes and then send them. You'll need to edit the
script to put the correct database details, power meter id, authorisation token
and device details. To set it to run every fifteen minutes, I use cron. Either
add an entry to your own crontab by running "crontab -e" then entering the
following line:

```
*/15 * * * * /path/to/google_powermeter_update.pl &gt; /dev/null
```

Or by creating a file containing the line below and copying it to
/etc/cron.d/powermeter_update.cron.

```
*/15 * * * * nobody /path/to/google_powermeter_update.pl &gt; /dev/null
```

In both cases, you can change the output redirection from "/dev/null" to e.g.
"/tmp/powermeter" to allow you to check any error codes in case of a problem.

Now go to <http://www.google.com/powermeter/site/> to check your data! Here's
an example of mine:

[![powermeter example](/blog/uploads/2010/06/powermeter-example-300x138.png)](/blog/uploads/2010/06/powermeter-example.png)

# Possible changes
The above description and scripts aren't ideal - if you lose your internet
connection then data will still be recorded but won't be sent to google. One
possible change would be to add a column to the database to list whether that
particular piece of data had been sent or not, which would allow all data to
eventually be sent and deleted afterwards if desired.

A second way around this would be to make use of the historical data that the
CurrentCost monitors use. This could also be a way of reducing the need to log
things ourselves.

# Conclusion
I hope this is of use to you - please let me know if you have any problems with
any of the above steps.

[post on using Google Powermeter]: /blog/2010/03/google-powermeter/
[perl]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/cc128_read.pl
[python]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/cc128_read.py
[cc128_parse.pl]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/cc128_parse.pl
[cc128_log_mysql.pl]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/cc128_log_mysql.pl
[2cheap2meter]: http://2cheap2meter.blogspot.com/2010/03/setting-up-google-powermeter.html
[google_powermeter_update.pl]: http://bitbucket.org/oojah/mosquitto/src/tip/misc/currentcost/google_powermeter_update.pl
