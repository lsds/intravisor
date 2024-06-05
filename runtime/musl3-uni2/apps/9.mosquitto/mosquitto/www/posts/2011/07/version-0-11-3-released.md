<!--
.. title: Version 0.11.3 released
.. slug: version-0-11-3-released
.. date: 2011-07-07 13:37:26
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release.

 * Don't complain and quit if `persistence_file` option is given (bug #802423).
 * Initialise listeners correctly when clients with duplicate client ids
   connect. Bug #801678.
 * Memory tracking is now disabled for Symbian builds due to lack of malloc.h.
 * Fix memory tracking compilation for kFreeBSD.
 * Python callbacks can now be used with class member functions.
 * Fix persistent database writing of client message chunks which caused errors
   when restoring (bug #798164)

Thanks to Neil Bothwick, Yuvraaj Kelkar, Craig Hollabaugh, Karl Palsson and
Andy Piper.
