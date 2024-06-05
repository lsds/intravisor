<!--
.. title: mqtt2pachube
.. slug: mqtt2pachube
.. date: 2012-02-06 22:41:58
.. tags: Solutions, Obsolete
.. category:
.. link:
.. description:
.. type: text
-->

I've written a tool to help get data from mqtt to [pachube]. Existing pachube
libraries offer good support for updating feeds that have a single datastream
or updating all feeds in a datastream, but seem to offer limited support for
updating an arbitrary datastream on its own. This can make life difficult when
your data is coming in from sensors as individual messages.

[mqtt2pachube] allows you to choose what mqtt subscriptions to make and then
match incoming messages by their topics to a pachube feed and datastream id.

At the moment it is still experimental, but seems to work. It has highlighted a
shortcoming in the mosquitto client library, so requires version 0.15.90 (ie.
the in-progress work for the next release). There is no Windows support for the
moment and no binary packages either. If you are interested in giving it a try,
you will have to compile it yourself. If you need help, please get in touch.

There are two examples of feeds created through mqtt2pachube using data from
[test.mosquitto.org]

 * [test.mosquitto.org details]
 * [UK energy data - generation source percentage]

[pachube]: http://pachube.com/
[mqtt2pachube]: http://bitbucket.org/oojah/mqtt2pachube
[test.mosquitto.org details]: https://pachube.com/feeds/43810
[UK energy data - generation source percentage]: https://pachube.com/feeds/47080
[test.mosquitto.org]: http://test.mosquitto.org/
