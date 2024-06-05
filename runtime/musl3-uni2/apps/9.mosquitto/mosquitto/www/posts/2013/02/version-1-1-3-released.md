<!--
.. title: Version 1.1.3 released
.. slug: version-1-1-3-released
.. date: 2013-02-11 22:13:21
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a minor bugfix release that addresses some problems identified during
Debian packaging.

# Broker

 * mosquitto_passwd utility now uses tmpfile() to generate its temporary data
   storage file. It also creates a backup file that can be used to recover data
   if an errors occur.

<h4>Other</h4>

 * Build script fixes to help packaging on Debian.
