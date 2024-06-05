<!--
.. title: Unintended change of behaviour in 1.3.4
.. slug: unintended-change-of-behaviour-in-1-3-4
.. date: 2014-10-10 09:35:32
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

Version 1.3.4 introduced the change that when using TLS with
`require_certificate` set to false, the client is no longer asked for a client
certificate. This seemed to be causing problems in some situations,
particularly with embedded devices.

If `use_identity_as_username` is set to true when `require_certificate` is set
to false, then the client will not be asked for a certificate, even if it has
one configured. This means that the client will be refused access with connack
code 4, "bad username or password", because if `use_identity_as_username`
currently requires that a certificate is present, even if `allow_anonymous` is
set to true.

This change may cause unexpected results, but does not represent a security
flaw because the change results in more clients being rejected than would
otherwise have been.
