<!--
.. title: Mosquitto Debian repo key updated
.. slug: mosquitto-debian-repo-key-updated
.. date: 2018-01-05 22:09:10
.. tags: Packaging
.. category:
.. link:
.. description:
.. type: text
-->

If you are using the [debian repository] at repo.mosquitto.org you may have
noticed that the repository signing key expired at the end of 2017. To get the
updated key use the following commands:

```
wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
sudo apt-key add mosquitto-repo.gpg.key
```

[debian repository]:/blog/2013/01/mosquitto-debian-repository
