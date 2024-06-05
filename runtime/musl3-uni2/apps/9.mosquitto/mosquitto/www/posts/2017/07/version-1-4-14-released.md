<!--
.. title: Version 1.4.14 released
.. slug: version-1-4-14-released
.. date: 2017-07-11 00:13:42
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

Version 1.4.13 contained a regression that meant persistence data was only
being saved after client information had been freed. This release fixes that.

If you use persistence then it is strongly recommended to avoid 1.4.13 so you
do not suffer data loss.
