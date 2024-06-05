<!--
.. title: Version 0.8.1 released
.. slug: version-0-8-1-released
.. date: 2010-08-11 23:47:18
.. tags: Packaging,Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a minor release. The primary reason for it is the amount of interest in
the Python interface to libmosquitto. This release tidies up the Python
interface considerably (it is now more "Pythonic" and easier to use), and
significantly, brings the promised packages.

This release also provides a few fixes, including to the packaging and
installation scripts. Unfortunately, it does also include a known bug that was
fixed prior to release, but accidentally left unmerged. This affects
mosquitto_pub client when using the -l option (publish line by line input from
stdin), causing it to exhibit high cpu load. I'll make a new bug fix release in
a few days with this and any other fixes that come up.

This release also provides improved packaging options. All of the available
options are now packaged for Ubuntu, including the libmosquitto0-python
package. Because there are now multiple packages, it is possible to provide
some mosquitto functionality on distributions where the version of sqlite3 is
too old. The packages available on these systems are listed as "clients only":

 * Fedora 12, 13 (full support)
 * openSUSE 11.3 (full support)
 * openSUSE 11.1, 11.2 (clients only)
 * Redhat Enterprise Linux 5 (clients only)
 * CentOS 5 (clients only)

Details are available on the [download page]. Please note that some
distributions have different naming schemes, so the Python module can be called
both python-mosquitto and libmosquitto0-mosquitto for example.

[download page]: /download
