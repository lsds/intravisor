<!--
.. title: Version 0.11.2 released
.. slug: version-0-11-2-released
.. date: 2011-06-26 21:30:34
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Don't free contexts in mqtt3_context_disconnect() (bug #799688 / #801678).
 * Only free will if present when freeing a client context.
