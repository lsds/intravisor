<!--
.. title: Distro packaging
.. slug: distro-packaging
.. date: 2010-11-07 12:02:58
.. tags: Packaging
.. category:
.. link:
.. description:
.. type: text
-->

Starting with version 0.9, I plan on getting mosquitto packaged in the major
Linux distributions. By this I mean Debian, Fedora, openSUSE and Ubuntu.  This
is my understanding of the current state of play of those distributions. Feel
free to correct me!

 * Debian is currently in freeze for the Squeeze release. Mosquitto will have
   to go into Squeeze+1, although it can still be uploaded to Unstable.
 * Fedora 14 has just been released, Fedora 15 will have feature freeze on the
   8th of February.
 * openSUSE 11.4 will have feature freeze at the start of December.
 * Ubuntu 11.04 has its Debian import freeze on the 30th of December and
   feature freeze on 24th of February.

The plan is therefore to release 0.9 around the 14th of November and aim to be
packaged for Debian unstable before 30th of December and openSUSE before the
start of December, with packaging for Fedora 15 coming at some point later. If
packaging for Debian unstable isn't possible before the Ubuntu import freeze,
then package for Ubuntu separately.

If you can help out with the packaging process for any of the above, I'd love
to hear from you. If your distribution isn't included and you'd like it to be,
get in touch as well and we'll see what's possible.

Finally, this won't stop me producing Ubuntu PPA or openSUSE build service
packaged binaries for those that prefer to stay at the cutting
edge.
