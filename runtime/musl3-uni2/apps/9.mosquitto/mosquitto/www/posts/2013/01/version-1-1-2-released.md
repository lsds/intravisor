<!--
.. title: Version 1.1.2 released
.. slug: version-1-1-2-released
.. date: 2013-01-30 22:12:35
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

# Client library

 * Fix `tls_cert_reqs` not being set to `SSL_VERIFY_PEER` by default. This
   meant that clients were not verifying the server certificate when connecting
   over TLS. This affects the C, C++ and Python libraries.

Source and binaries are available on the [download page].

[download page]: /download
