<!--
.. title: Mosquitto and current unreleased libwebsockets branch
.. slug: mosquitto-and-current-unreleased-libwebsockets-branch
.. date: 2015-05-10 20:51:11
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

The current unreleased libwebsockets master branch defines the VERSION macro in
its header files. I believe this to be a bug in libwebsockets.

This bug causes compilation of mosquitto with websockets support to fail.

Please use a released version of libwebsockets, either 1.2, 1.3 or 1.4.
Mosquitto will compile with all of these versions.

I do not recommend using an unreleased version of libwebsockets, the project is
not shy about making ABI/API incompatible changes between releases so it is
impractical to provide support for.
