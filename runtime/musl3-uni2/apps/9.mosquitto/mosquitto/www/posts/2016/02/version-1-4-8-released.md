<!--
.. title: Version 1.4.8 released
.. slug: version-1-4-8-released
.. date: 2016-02-14 19:15:33
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a security bugfix release. Any users of the `mount_point` feature are
strongly advised to upgrade because versions prior to 1.4.8 allow clients to
inject messages outside of their `mount_point` through the use of a Will.

# Broker

 * Wills published by clients connected to a listener with `mount_point` defined
   now correctly obey the mount point. This was a potential security risk
   because it allowed clients to publish messages outside of their restricted
   mount point. This is only affects brokers where the `mount_point` option is in
   use. Closes [#487178].
 * Fix detection of broken connections on Windows. Closes [#485143].
 * Close stdin etc. when daemonised. Closes [#485589].
 * Fix incorrect detection of FreeBSD and OpenBSD. Closes [#485131].

# Client library

 * `mosq-&gt;want_write` should be cleared immediately before a call to
   `SSL_write`, to allow clients using `mosquitto_want_write()` to get accurate
   results.

[#487178]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=487178
[#485143]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=485143
[#485589]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=485589
[#485131]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=485131
