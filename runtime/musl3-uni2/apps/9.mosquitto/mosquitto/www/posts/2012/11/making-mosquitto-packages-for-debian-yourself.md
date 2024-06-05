<!--
.. title: Making Mosquitto packages for Debian yourself
.. slug: making-mosquitto-packages-for-debian-yourself
.. date: 2012-11-27 16:26:41
.. tags: Packaging,Solutions
.. category:
.. link:
.. description:
.. type: text
-->

As Debian has been in feature freeze since before Mosquitto 1.0 was released,
it will be a long time until there is an updated version of Mosquitto in
Debian. It is, however, fairly straightforward to do the packaging yourself.
Here's how to do that from the command line.

Download and unpack the mosquitto source tarball:

```
wget http://mosquitto.org/files/source/mosquitto-1.1.2.tar.gz
tar -zxf mosquitto-1.1.2.tar.gz
```

Rename the tarball to match Debian requirements:

```
mv mosquitto-1.1.2.tar.gz mosquitto_1.1.2.orig.tar.gz
```

The current mosquitto packaging files are available at
<https://packages.debian.org/source/stable/mosquitto> - you want the
.debian.tar.xz.

The next step is to build the package, but you may find that you need to
install some packages first:

```
sudo apt-get install build-essential python quilt libwrap0-dev libssl-dev devscripts python-setuptools
```

To build the packages do

```
cd mosquitto-1.1.2/
debuild
```

You should now have a list of .deb files in the parent directory which you can
install with:

```
sudo dpkg -i &lt;deb file&gt;
```

Please leave comments if you find this useful or have any problems.
