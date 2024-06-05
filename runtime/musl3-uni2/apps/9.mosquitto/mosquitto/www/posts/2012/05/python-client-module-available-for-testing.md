<!--
.. title: Python client module available for testing
.. slug: python-client-module-available-for-testing
.. date: 2012-05-07 01:17:57
.. tags: Solutions,Testing
.. category:
.. link:
.. description:
.. type: text
-->

As part of the ongoing work on mosquitto 0.16, the libmosquitto C client
library has been ported to Python. It provides complete MQTTv3.1 support and
will eventually remove the need for the current Python wrapper around the C
library and will allow it to be used more easily and in more situations.

The interface is largely the same as the existing Python wrapper. The
differences are that it uses the current development interface which differs
slightly from that in 0.15 (see the [Python documentation]), not all of the new
interface is implemented - there is no threading support and finally some
datatypes may be more Python like (e.g. lists in `on_subscribe()` callback
rather than an integer).

The conversion from ~4000 lines C to ~1000 lines Python took just two evenings
and is now ready for testing. It is available in the 0.16 branch in the
[bitbucket repository], or as a single file at
<http://mosquitto.org/files/python/mosquitto.py>

Please give it a try and report any bugs you find using any of the methods on
the [Support page].

Please note that the new Python module does not currently support Python 3.

[Python documentation]: /documentation/python
[bitbucket repository]: https://bitbucket.org/oojah/mosquitto/src/b9e04ef2a762/lib/python/mosquitto.py
[Support page]: /support
