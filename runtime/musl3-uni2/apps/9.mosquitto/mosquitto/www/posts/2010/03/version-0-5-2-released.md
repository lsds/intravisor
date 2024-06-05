<!--
.. title: Version 0.5.2 released
.. slug: version-0-5-2-released
.. date: 2010-03-02 16:29:22
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release; it is recommended that you upgrade to this version:

 * Always update last backup time, so that the backup doesn't run every time
   through the main loop once `autosave_interval` has been reached.
 * Report $SYS/broker/uptime in the same format as rsmb.
 * Make mandatory options obvious in usage output and man page of
   mosquitto_pub. Fixes bug [#529990].
 * Treat subscriptions with a trailing slash correctly. This should fix bugs
   [#530099] and [#530369].

Mosquitto is now also available for Linux x86 statically compiled against
sqlite3, which makes it usable on older distributions such as Ubuntu Hardy that
are still supported but do not have a sufficiently new version of sqlite3. To
download this package, go to the [download page].

[#529990]: https://bugs.launchpad.net/mosquitto/+bug/529990
[#530099]: https://bugs.launchpad.net/mosquitto/+bug/530099
[#530369]: https://bugs.launchpad.net/mosquitto/+bug/530369
[download page]: /download
