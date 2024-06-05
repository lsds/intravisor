<!--
.. title: Version 0.5.4 released
.. slug: version-0-5-4-released
.. date: 2010-03-14 18:28:15
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Fix memory allocation in `mqtt3_fix_sub_topic()` ([bug #531861]).
 * Remove accidental limit of 100 client connections.
 * Fix mosquitto_pub handling of messages with QoS&gt;0 ([bug #537061]).

[bug #531861]: https://bugs.launchpad.net/mosquitto/+bug/531861
[bug #537061]: https://bugs.launchpad.net/mosquitto/+bug/537061
