<!--
.. title: Version 0.10.1 released
.. slug: version-0-10-1-released
.. date: 2011-05-12 10:32:11
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release primarily for Windows users.

 * Fix Windows compilation.
 * Fix mosquitto.py on Windows - call lib init/cleanup.
 * Don't abort when connecting if given an unknown address type (assuming
   an IPv4 or IPv6 address is given).

Please see the [download page].

Thanks to Karl Palsson.

[download page]: /download
