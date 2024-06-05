<!--
.. title: Debian and Ubuntu packaging
.. slug: debian-and-ubuntu-packaging
.. date: 2011-07-10 23:16:24
.. tags: Packaging
.. category:
.. link:
.. description:
.. type: text
-->

I'm very pleased to say that Mosquitto is very nearly packaged in Debian and
Ubuntu. In truth, 0.10 is packaged and uploaded for both Debian testing
(Wheezy) and Ubuntu Oneiric Ocelot, but there is a problem with the config that
means it won't restart properly. That is fixed with the 0.11.3 upload which is
now in unstable. That means after 10 days and it will be in Debian testing for
all to use. I've also submitted a sync request with Ubuntu ([bug #808530])
to ensure it makes it across. I'll still be maintaining the
Launchpad PPA for older versions of Ubuntu.

Thanks to the Debian developer Michael Tautschnig for reviewing my package and
doing the upload.

[bug #808530]: https://bugs.launchpad.net/ubuntu/+source/mosquitto/+bug/808530
