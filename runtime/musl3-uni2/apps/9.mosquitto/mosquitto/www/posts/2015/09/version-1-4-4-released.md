<!--
.. title: Version 1.4.4 released
.. slug: version-1-4-4-released
.. date: 2015-09-19 09:53:33
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Don't leak sockets when outgoing bridge with multiple addresses cannot
 * connect. Closes [#477571].
 * Fix cross compiling of websockets. Closes [#475807].
 * Fix memory free related crashes on openwrt and FreeBSD. Closes [#475707].
 * Fix excessive calls to message retry check.

[#477571]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=477571
[#475707]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=475707
[#475807]: https://bugs.eclipse.org/bugs/show_bug.cgi?id=475807
