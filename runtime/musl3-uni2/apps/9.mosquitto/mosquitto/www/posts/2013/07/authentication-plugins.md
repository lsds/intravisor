<!--
.. title: Authentication plugins
.. slug: authentication-plugins
.. date: 2013-07-18 22:27:45
.. tags: Solutions
.. category:
.. link:
.. description:
.. type: text
-->

There has been some interest in authentication plugins for mosquitto recently.
Some examples have appeared:

Authentication based on md5 hashes: [mosquitto_auth_plugin_md5]

Authentication based on md5 hashed passwords in postgresql:
[mosquitto_auth_plugin_pg_md5]

Authentication and topic ACL with redis and a PBKDF2
hash: [mosquitto-redis-auth]

I particularly like the redis based plugin for the interesting additions like
the "superuser" that is exempt from ACL checks.

If you've written an auth plugin and think it might be useful to others, let me
know.

[mosquitto_auth_plugin_md5]: https://github.com/sskaje/mosquitto_auth_plugin_md5
[mosquitto_auth_plugin_pg_md5]: https://github.com/sebaroesch/mosquitto_auth_plugin_pg_md5
[mosquitto-redis-auth]: https://github.com/jpmens/mosquitto-redis-auth
