<!--
.. title: Version 1.0.5 released
.. slug: version-1-0-5-released
.. date: 2012-11-03 12:29:16
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Broker

 * Fix crash when the broker has `use_identity_as_username` set to true but a
   client connects without a certificate.
 * mosquitto_passwd should only be installed if `WITH_TLS=yes`.

# Library

 * Use symbolic errno values rather than numbers in Python module to avoid
   cross platform issues (incorrect errno on Mac OS).

# Other

 * Build script fixes for FreeBSD.
