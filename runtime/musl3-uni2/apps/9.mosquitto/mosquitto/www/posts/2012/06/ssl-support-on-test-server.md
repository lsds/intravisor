<!--
.. title: SSL support on Test Server
.. slug: ssl-support-on-test-server
.. date: 2012-06-30 15:15:57
.. tags: Testing
.. category:
.. link:
.. description:
.. type: text
-->

The next version of Mosquitto will provide SSL support for network encryption
and authentication. This work is still in development, but is sufficiently
advanced to make available for testing on [test.mosquitto.org]. In addition to
the existing unencrypted access via port 1883, connections are now possible on
ports 8883 and 8884.

Port 8883 provides simple encrypted access. Your client should verify the
server certificate using the CA certificate available at
<http://test.mosquitto.org/ssl/mosquitto.org.crt>

Port 8884 uses the same server certificate, but requires that your client
provide a valid certificate signed by the mosquitto.org CA key. If you wish to
obtain a client certificate for testing purposes, please get in touch.

The development Python module provides client SSL support. The latest version
is available at [mosquitto.py] with a simple example at [ssub.py].  You will
need to place the mosquitto.org CA certificate linked above in the same
directory. All versions of Python from 2.7 upwards (including Python 3) are
supported.

Please get in touch if you have any problems.

Update:

All clients in the development version now support SSL.

[test.mosquitto.org]: http://test.mosquitto.org/
[mosquitto.py]: http://test.mosquitto.org/ssl/mosquitto.py
[ssub.py]: http://test.mosquitto.org/ssl/ssub.py
