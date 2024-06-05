<!--
.. title: Version 0.15 released
.. slug: version-0-15-released
.. date: 2012-02-05 09:26:41
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a feature and bugfix release.

 * Implement "once" and "lazy" bridge start types.
 * Add support for $SYS/broker/clients/maximum and $SYS/broker/clients/active
   topics.
 * Add support for $SYS messages/byte per second received/sent topics.
 * Updated mosquitto man page - $SYS hierarchy and signal support were out of
   date.
 * Auto generated pub/sub client ids now include the hostname.
 * Tool for dumping persistent DB contents is available in src/db_dump. It
   isn't installed by default.
 * Enforce topic length checks in client library.
 * Add new return type `MOSQ_ERR_ERRNO` to indicate that the errno variable
   should be checked for the real error code.
 * Add support for `connection_messages` config option.
 * mosquitto_sub will now refuse to run if the -c option (disable clean
   session) is given and no client id is provided.
 * mosquitto_pub now gives more useful error messages on invalid input or other
   error conditions.
 * Fix Python `will_set()` true/True typo.
 * Fix messages to topic `a/b` incorrectly matching on a subscription `a` if
   another subscription `a/#` exists.
