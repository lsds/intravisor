<!--
.. title: Version 1.4 released
.. slug: version-1-4-released
.. date: 2015-02-18 21:23:04
.. tags: Releases
.. category:
.. link:
.. description:
.. type: text
-->

This is a feature release and is also the first release of the mosquitto
project from the Eclipse Foundation umbrella. The code is now dual licenced
under the [EPL]. The EDL and BSD 3 clause license are essentially identical so
if you were happy with the BSD license then you should be happy with the EDL.

Files distributed will remain in the same place but will in some cases also be
available on the Eclipse download servers.

# Important changes

 * Websockets support in the broker.
 * Bridge behaviour on the local broker has changed due to the introduction of
   the `local_*` options. This may affect you if you are using authentication 
   and/or ACLs with bridges.
 * The default TLS behaviour has changed to accept all of TLS v1.2, v1.1 and
   v1.0, rather than only one version of the protocol. It is still possible to
   restrict a listener to a single version of TLS.
 * The Python client has been removed now that the Eclipse Paho Python client
   has had a release.
 * When a durable client reconnects, its queued messages are now checked
   against ACLs in case of a change in username/ACL state since it last
   connected.
 * New `use_username_as_clientid` option on the broker, for preventing
   hijacking of a client id.
 * The client library and clients now have experimental SOCKS5 support.
 * Wildcard TLS certificates are now supported for bridges and clients.
 * The clients have support for config files with default options.
 * Client and client libraries have support for MQTT v3.1.1.
 * Bridge support for MQTT v3.1.1.

# Broker

 * Websockets support in the broker.
 * Add `local_clientid`, `local_username`, `local_password` for bridge
   connections to authenticate to the local broker.
 * Default TLS mode now accepts TLS v1.2, v1.1 and v1.0.
 * Support for ECDHE-ECDSA family ciphers.
 * Fix bug #1324411, which could have had unexpected consequences for delayed
   messages in rare circumstances.
 * Add support for `session present` in CONNACK messages for MQTT v3.1.1.
 * Remove strict protocol #ifdefs.
 * Change $SYS/broker/clients/active -&gt; $SYS/broker/clients/connected
 * Change $SYS/broker/clients/inactive -&gt; $SYS/broker/clients/disconnected
 * When a durable client reconnects, its queued messages are now checked
   against ACLs in case of a change in username/ACL state since it last
   connected.
 * libuuid is used to generate client ids, where it is available, when an MQTT
   v3.1.1 client connects with a zero length client id.
 * Anonymous clients are no longer accidently disconnected from the broker
   after a SIGHUP.
 * mosquitto_passwd now supports `-b` (batch mode) to allow the password to be
   provided at the command line.
 * Removed $SYS/broker/changeset. This was intended for use with debugging, but
   in practice is of no use.
 * Add support for `use_username_as_clientid` which can be used with
   authentication to restrict ownership of client ids and hence prevent one
   client disconnecting another by using the same client id.
 * When `require_certificate` was false, the broker was incorrectly asking for
   a certificate (but not checking it). This caused problems with some clients
   and has been fixed so the broker no longer asks.
 * When using syslog logging on non-Windows OSs, it is now possible to specify
   the logging facility to one of local0-7 instead of the default "daemon".
 * The `bridge_attempt_unsubscribe` option has been added, to allow the sending
   of UNSUBSCRIBE requests to be disabled for topics with "out" direction.
   Closes bug #456899.
 * Wildcard TLS certificates are now supported for bridges.
 * Support for "hour" client expiration lengths for the
   `persistent_client_expiration` option. Closes bug #425835.
 * Bridge support for MQTT v3.1.1.
 * Root privileges are now dropped after starting listeners and loading
   certificates/private keys, to allow private keys to have their permissions
   restricted to the root user only. Closes bug #452914.
 * Usernames and topics given in ACL files can now include a space. Closes bug
   #431780.
 * Fix hang if pattern acl contains a %u but an anonymous client connect.
   Closes bug #455402.
 * Fix man page installation with cmake. Closes bug #458843.
 * When using `log_dest file` the output file is now flushed periodically.

# Clients

 * Both clients can now load default configuration options from a file.
 * Add `-C` option to mosquitto_sub to allow the client to quit after receiving
   a certain count of messages. Closes bug #453850.
 * Add `--proxy` SOCKS5 support for both clients.
 * Pub client supports setting its keepalive. Closes bug #454852.
 * Add support for config files with default options.
 * Add support for MQTT v3.1.1.

# Client library

 * Add experimental SOCKS5 support.
 * mosquitto_loop_forever now quits after a fatal error, rather than blindly
   retrying.
 * SRV support is now not compiled in by default.
 * Wildcard TLS certificates are now supported.
 * mosquittopp now has a virtual destructor. Closes bug #452915.
 * Add support for MQTT v3.1.1.
 * Don't quit mosquitto_loop_forever() if broker not available on first
   connect. Closes bug #453293, but requires more work.

# Dependencies

This release introduces two new dependencies, libwebsockets and libuuid. Both
are optional. libuuid comes from the e2fsprogs project and allows the broker to
generate random client ids for MQTT v.3.1.1. The libwebsockets dependency can
use either libwebsockets 1.3 or 1.2.x, with 1.3 being the preferred
choice.

[EPL]: https://www.eclipse.org/legal/epl-v10.html
[EDL]: https://eclipse.org/org/documents/edl-v10.php
