<!--
.. title: Version 0.8 released
.. slug: version-0-8-released
.. date: 2010-08-08 10:31:17
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is the library release. There are a few bug fixes and changes of behaviour
for the mosquitto and the clients, but the significant part of this release is
the new mosquitto MQTT client library. The library comes in three flavours: the
C library, which is the main library, and C++ and Python bindings. If you're
interested in helping add bindings for your favourite language, please get in
touch.

The library interface (API) is to be considered experimental, although I
believe the C and C++ APIs to be complete and sane. The Python bindings are a
naïve attempt by a C programmer and will definitely be changing in the future
to something more pythonic. I'd be extremely grateful for help from experienced
python programmers to this end.

The documentation of the library is currently ongoing... There is an overview
of most of the function calls and an example in the [libmosquitto.3] man page,
but complete coverage can be found in the mosquitto.h man page. This, combined
with the class details in mosquittopp.h can be used to help use the C++
library. The python module isn't documented due to its extremely changeable
state, but there is an example in the python directory.

Other changes:

 * Topics starting with a / are treated as distinct to those not starting with
   a /. For example, /topic/path is different to topic/path. This matches the
   behaviour of rsmb.
 * Correctly calculate the will QoS on a new client connection (bug #597451).
 * Add "addresses" configuration file variable as an alias of "address", for
   better rsmb compatibility.
 * Bridge `clean_session` setting is now false, to give more sensible behaviour
   and be more compatible with rsmb.
 * Add `cleansession` variable for configuring bridges.
 * Add `keepalive_interval` variable for bridges.
 * Remove default topic subscription for mosquitto_sub because the old
   behaviour was too confusing.
 * Added a C client library, which the pub and sub clients now use.
 * Added a C++ client library (bound to the C library).
 * Added a Python client library (bound to the C library).
 * Added CMake build scripts to allow the library and clients (not the broker)
   to be compiled natively on Windows.

Get it from the [download page].

The change to using a library means that packaging mosquitto for distros  is a
lot more complex. This is stretching my packaging experience, so  please bear
with me on that front! Mosquitto will now likely consist of a number of
different packages on Ubuntu at least:

 * mosquitto (the broker)
 * mosquitto-clients (mosquitto_sub, mosquitto_pub)
 * libmosquitto0 (C library)
 * libmosquitto0-dev (C library development files)
 * libmosquittopp0 (C++ library)
 * libmosquittopp0-dev (C++ library development files)
 * libmosquitto-python (Python binding)

# Update
I've been getting a few questions about the python interface. This isn't
currently packaged for Ubuntu, but hopefully will be soon. There are basic
python examples in the downloads at lib/python/sub.py and
misc/currentcost/gnome-panel/CurrentCostMQTT.py

[libmosquitto.3]: /man/libmosquitto-3.html
[download page]: /download
