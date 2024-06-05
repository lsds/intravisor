<!--
.. title: Version 0.5.1 released
.. slug: version-0-5-1-released
.. date: 2010-03-01 09:26:28
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This announcement summarises the changes in both 0.5 and 0.5.1.

The interesting changes:

 * Add mosquitto_sub and mosquitto_pub, simple clients for subscribe/publish.
 * Change persistence behaviour. The database is now stored in memory even if
   persistence is enabled. It is written to disk when mosquitto exits and also
   at periodic intervals as defined by the new `autosave_interval` option. This
   makes persistence more suitable when being used on devices with a limited
   number of writes, such as flash.
 * Default sqlite3-pcre path on Linux is now /usr/lib/sqlite3/pcre.so to match
   new sqlite3-pcre packages.

The less interesting/bug fixes:

 * No longer store QoS=0 messages for disconnected clients that do not have
   clean start set.
 * Rename `msg_timeout` option to `retry_interval` for better rsmb
   compatibility.
 * The writing of the persistence database may be forced by sending mosquitto
   the SIGUSR1 signal.
 * Clients that do not send CONNECT as their first command are now
   disconnected.
 * Boolean configuration values may now be specified with true/false as well as
   1/0.
 * Log message on CONNECT with invalid protocol or protocol version.
 * Add man pages for clients.
 * Add general man page on mqtt.
 * Root privileges are now dropped only after attempting to write a pid file
   (if configured). This means that the pid file can be written to /var/run/
   directly and should fix bug #523183.
