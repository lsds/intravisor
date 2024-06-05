<!--
.. title: Two!
.. slug: two
.. date: 2011-10-25 23:46:24
.. tags: Events
.. category:
.. link:
.. description:
.. type: text
-->

Today (just) marks the 2nd birthday of the mosquitto project. In the past year
mosquitto has undergone pretty substantial changes and improvements. Some
highlights from the year:

 * Move away from using sqlite to store data in memory and on disk, resulting
   in a much more compact, better performing and *more elegant* broker
 * Windows native port
 * MQTT 3.1 support
 * Greatly improved Python module
 * Getting really close to being feature complete with respect to RSMB
 * Being packaged in Debian...
 * ... and Ubuntu
 * The mosquitto client code being used by Facebook in their iphone app
 * The numerous bugs reported, bugfixes, suggestions and general interest
   displayed by people. Thanks everyone!

Mosquitto has gone from version 0.8.3 to 0.13 - so what about next year? This
will be the year when 1.0 is released. The bar I'm setting is complete RSMB
features, with the exception of some of the more esoteric ones. At the moment
this means there are still some of the bridge features to implement and
complete configuration reloading. I'm also going to have a much improved
Windows port so there will be no need for a separate Cygwin version. At the
same time I'm making a Windows installer and allowing mosquitto to be installed
as a proper Windows service. This work should all be in 0.14. Another point for
improvement is the Python module - it could be more Pythonic than it is now. My
current plan is to have it throw exceptions rather than return integer error
values but I could do with the help of a Python expert really.

All in all I think it should be a good year.
