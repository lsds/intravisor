<!--
.. title: Upgrading to 0.5.1
.. slug: upgrading-to-0-5-1
.. date: 2010-03-01 09:48:41
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

When upgrading to 0.5.1 from 0.4 or higher, there is an important change in the
location of the sqlite3-pcre library used. On Linux, the expected location of
this library has changed from /usr/lib/sqlite3-pcre.so to
/usr/lib/sqlite3/pcre.so. This is because the library is an extension
specifically for sqlite3, not a general use shared library.

If you installed sqlite3-pcre manually, or are not using Ubuntu, you should
either modify the `ext_sqlite3_regex` option in /etc/mosquitto.conf to point to
your library path, or move the library to the new location.

If you are using Ubuntu and have installed mosquitto from the launchpad ppa,
this will largely be taken care of. However, due to a mistake in the packaging
of sqlite3-pcre, you must first remove sqlite3-pcre with your package manager
and then reinstall it before updating mosquitto. You will only ever need to do
this once.

Sorry for the inconvenience caused by this change. If you have any problem or
questions, feel free to get in touch on the [mqtt users mailing list].

[mqtt users mailing list]: https://launchpad.net/~mqtt-users
