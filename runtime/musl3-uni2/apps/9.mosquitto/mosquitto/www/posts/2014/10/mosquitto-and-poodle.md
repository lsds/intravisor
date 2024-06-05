<!--
.. title: Mosquitto and POODLE
.. slug: mosquitto-and-poodle
.. date: 2014-10-16 15:53:33
.. tags: Security
.. category:
.. link:
.. description:
.. type: text
-->

Details of the POODLE attack that targets SSLv3 have been released recently.
Mosquitto has never provided support for SSLv3 (or SSLv2) so should not be
vulnerable to this attack and does not require any configuration
changes.
