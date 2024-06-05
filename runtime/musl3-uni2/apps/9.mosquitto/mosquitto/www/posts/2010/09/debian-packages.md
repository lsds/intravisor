<!--
.. title: Debian packages
.. slug: debian-packages
.. date: 2010-09-27 20:14:50
.. tags: Packaging,Releases
.. category:
.. link:
.. description:
.. type: text
-->

I've created some packages for Debian on i386 and amd64. They can be found at
<http://mosquitto.org/files/binary/debian/>. They are almost identical to the
Ubuntu packages (Debian doesn't use upstart, so there is a different init
script), but compiled against Debian testing (Squeeze) instead. This is because
Debian 5 (Lenny) doesn't include a recent enough version of sqlite3.

Please let me know if you have any problems with the packages.
