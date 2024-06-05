<!--
.. title: Version 0.5.3 released
.. slug: version-0-5-3-released
.. date: 2010-03-03 22:03:26
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Will messages are now only sent when a client disconnects  unexpectedly.
 * Fix all incoming topics/subscriptions that start with a / or  contain
   multiple / in a row (//). This should finally fix bug [#530099].
 * Do actually disconnect client when it sends an empty  subscription/topic
   string.
 * Add missing $SYS/broker/clients/total to man page.

[#530099]: https://bugs.launchpad.net/mosquitto/+bug/530099
