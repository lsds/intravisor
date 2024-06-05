<!--
.. title: Using Let's Encrypt certificates with mosquitto
.. slug: using-lets-encrypt-certificates-with-mosquitto
.. date: 2015-12-13 19:53:37
.. tags: certificates,encryption,tls
.. category:
.. link:
.. description:
.. type: text
-->

If you want to use TLS certificates you've generated using the [Let's Encrypt]
service, this is how you should configure your listener (replace "example.com"
with your own domain of course):

Then use the following for your mosquitto.conf:

```
listener 8883
cafile /etc/ssl/certs/ISRG_Root_X1.pem
certfile /etc/letsencrypt/live/example.com/fullchain.pem
keyfile /etc/letsencrypt/live/example.com/privkey.pem
```

Since version 2.0 of Mosquitto, you can send a SIGHUP to the broker to cause it
to reload certificates. Prior to this version, mosquitto would never update
listener settings when running, so you will need to completely restart the
broker.

[Let's Encrypt]: https://letsencrypt.org/
