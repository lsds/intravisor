<!--
.. title: Mosquitto Debian repository
.. slug: mosquitto-debian-repository
.. date: 2013-01-10 22:43:37
.. tags: Packaging
.. category:
.. link:
.. description:
.. type: text
-->

On a previous post I described [how to make mosquitto debian packages]. This
turned out to be a bit problematic, so I've now put up an experimental debian
repository for mosquitto. It includes packages for the i386, amd64, armel and
raspberry pi (raspbian armhf ) architectures.

It's worth repeating that this is experimental - there are package changes that
haven't been vetted by a Debian developer so it's possible something will
break. I've tested myself and had no problems so far.

To use the new repository you should first import the repository package
signing key:

```
wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
sudo apt-key add mosquitto-repo.gpg.key
```

Then make the repository available to apt:

```
cd /etc/apt/sources.list.d/
```

Then one of the following, depending on which version of debian you are using:

```
sudo wget http://repo.mosquitto.org/debian/mosquitto-jessie.list
sudo wget http://repo.mosquitto.org/debian/mosquitto-stretch.list
sudo wget http://repo.mosquitto.org/debian/mosquitto-buster.list
```



Then update apt information:

```
apt-get update
```

And discover what mosquitto packages are available:

```
apt-cache search mosquitto
```

Or just install:

```
apt-get install mosquitto
```

[how to make mosquitto debian packages]: /blog/2012/11/making-mosquitto-packages-for-debian-yourself/
