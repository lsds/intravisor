<!--
.. title: Version 1.4.1 released
.. slug: version-1-4-1-released
.. date: 2015-04-03 11:12:03
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix and security release. Users of mosquitto 1.4 are strongly
advised to upgrade. Upgrading from earlier versions is recommended but not as
important.

# Broker

 * Fix possible crash under heavy network load. Closes [#463241]. This bug only
   affects version 1.4.
 * Fix possible crash when using pattern ACLs.
 * Fix problems parsing config strings with multiple leading spaces. Closes
   [#462154].
 * Websockets clients are now periodically disconnected if they have not
   maintained their keepalive timer. Closes [#461619].
 * Fix possible minor memory leak on acl parsing.

# Client library

 * Inflight limits should only apply to outgoing messages. Closes [#461620].
 * Fix reconnect bug on Windows. Closes [#463000].
 * Return -1 on error from `mosquitto_socket()`. Closes [#461705].
 * Fix crash on multiple calls to `mosquitto_lib_init`/`mosquitto_lib_cleanup`.
   Closes [#462780].
 * Allow longer paths on Windows. Closes [#462781].
 * Make `_mosquitto_mid_generate()` thread safe. Closes [#463479].

[#463241]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=463241
[#462154]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=462154
[#461619]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=461619
[#461620]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=461620
[#463000]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=463000
[#461705]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=461705
[#462780]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=462780
[#462781]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=462781
[#463479]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=463479
