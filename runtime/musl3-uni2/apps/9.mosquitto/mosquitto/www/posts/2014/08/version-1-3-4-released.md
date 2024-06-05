<!--
.. title: Version 1.3.4 released
.. slug: version-1-3-4-released
.. date: 2014-08-06 00:53:05
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release. The reason for the rapid release of the past two
versions is down to a Debian developer reviewing the mosquitto package. This is
a good opportunity to ensure that as bug free a version as possible is present
in Debian.

# Broker

 * Don't ask client for certificate when `require_certificate` is **false**.
 * Backout incomplete functionality that was incorrectly included in 1.3.2.

Binaries will follow shortly.
