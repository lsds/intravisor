<!--
.. title: Version 1.0.3 released
.. slug: version-1-0-3-released
.. date: 2012-09-27 14:06:28
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Broker

 * Fix loading of psk files.
 * Don't return an error when reloading config if an ACL file isn't defined. 
   This was preventing psk files being reloaded.
 * Clarify meaning of $SYS/broker/clients/total in mosquitto(8) man page.
 * Clarify meaning of $SYS/broker/messages/stored in mosquitto(8) man page.
 * Fix non-retained message delivery when subscribing to #.
 * Fix retained message delivery for subs to foo/# with retained messages at
   foo.
 * Include the filename in password/acl file loading errors.

# Library

 * Fix possible AttributeError when `self._sock == None` in Python module.
 * Fix reconnecting after a timeout in Python module.
 * Fix reconnecting when there were outgoing packets in the queue in the Python
   module.
 * Fix problem with mutex initialisation causing crashes on some Windows
   installations.

Source is available on the [download page], the binary packages for Windows are
available now and Linux builds will be available as soon as the various build
servers complete their tasks.

[download page]: /download
