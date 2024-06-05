<!--
.. title: Version 0.10.2 released
.. slug: version-0-10-2-released
.. date: 2011-06-01 20:20:37
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Don't abort when connecting if the first connection fails. This is important
   on e.g. Windows 7, where IPV6 is offered as the first choice but may not be
   available.
 * Deal with long logging messages properly (bug #785882).
 * Fix library compilation on Symbian - no pselect() available.
 * Don't stop processing subscriptions on received messages after a
   subscription with # matches. (bug #791206).

Please see the [download page].

Thanks again to Karl Palsson and Yuvraaj Kelkar.

[download page]: /download
