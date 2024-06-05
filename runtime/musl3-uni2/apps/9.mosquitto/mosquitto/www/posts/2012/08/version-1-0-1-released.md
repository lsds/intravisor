<!--
.. title: Version 1.0.1 released
.. slug: version-1-0-1-released
.. date: 2012-08-15 22:39:52
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a bugfix release. The important changes are fixing the `on_log()`
callback in the Python module and the `log_dest` option when running as a
Windows service. The rest of the fixes are documentation and build script
fixes.

Downloads are available on the [download page] and include all supported
binaries (except for Ubuntu packages which are still waiting to build due to
Launchpad maintenance). The Python module has been uploaded to [Python Package
Index].

# Broker

 * Fix default `log_dest` when running as a Windows service.

# Client library
 
 * Fix incorrect parameters in Python `on_log()` callback call. Fixes bug
   #1036818.

# Clients

 * Clients now don't display TLS/TLS-PSK usage help if they don't support it.

# Build scripts

 * Fix TLS-PSK support in the CMake build files.
 * Fix man page installation in the CMake build files.
 * Fix SYSCONFDIR in cmake on \*nix when installing to /usr. Fixes bug
   #1036908.

# Documentation
 
 * Fix mqtt/MQTT capitalisation in man pages.
 * Update compiling.txt.
 * Fix incorrect callback docs in mosquitto.py. Fixes bug #1036607.
 * Fix various doc typos and remove obsolete script. Fixes bug #1037088.

[download page]: /download
[Python Package Index]: http://pypi.python.org/pypi
