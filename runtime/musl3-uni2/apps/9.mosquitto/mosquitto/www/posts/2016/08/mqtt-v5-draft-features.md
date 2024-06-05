<!--
.. title: MQTT v5 draft features
.. slug: mqtt-v5-draft-features
.. date: 2016-08-15 19:23:48
.. tags: MQTT
.. category:
.. link:
.. description:
.. type: text
-->

The [MQTT Technical Committee] at OASIS continue to work on improvements to
MQTT. The next version looks set to be MQTT version 5 and has reached the
"working draft" stage. This post lists some of the changes that are in the
working draft 02 and so gives at least a flavour of the improvements coming up.
Take this with a pinch of salt, I may have missed some changes and there is no
commitment that any of these features will remain in the final specification as
they are described here.

# Session management

In MQTT v3.1.1 and earlier, a client could control how the server treats its
session with the clean session flag. If set to 1, the server would delete any
existing session for that client and would not persist the session after
disconnecting. If set to 0, the server would restore any existing session for a
client when it reconnected, and persist the session when the client
disconnected.

A session here means the subscriptions for a client and any queued messages.

The new spec changes this behaviour. The clean session flag has been renamed to
clean start (this was actually the name of the flag in the old MQTT v3 spec)
and now only affects how the broker handles a client session when the client
connects. If set to 1, the server discards any previous session information,
otherwise session information is kept.

To deal with removing of sessions at any other time, a new identifier/value
pair has been introduced. These identifier/value pairs are an addition to the
variable header part of some MQTT packets and allow configuring of different
behaviour. In the case of the CONNECT packet, a Session Expiry interval can be
specified which is a 4 byte integer that gives the number of seconds after a
client has disconnected that the server should remove session information for
that client. If the Session Expiry interval is absent from the CONNECT packet,
then the session will never expire. If it is set to 0, then the session is
removed as soon as the client disconnects.

The new clean start flag and session expiry interval allow the existing clean
session behaviour to be duplicated but also allow client sessions to be expired
based on time.

# Updated Connect Return codes

The return codes passed to the client in a CONNACK packet have been expanded to
include:

 * 6: Connection Refused, reason unspecified
 * 7: Connection Refused, implementation specific
 * 8: Connection Refused, CONNECT packet was malformed

# Repeated topics when publishing

When publishing data to a single topic, a new feature will help reduce
bandwidth use. A client or server can set the topic in a PUBLISH message to be
a zero length string. This tells the client/server being published to, to use
the previous topic instead. This goes some way to reducing the current overhead
associated with publishing - a shame it isn't quite as good as the registered
topics available in MQTT-SN.

# Payload Format Indicator

Another identifier/value pair is available for use when sending a PUBLISH
message. This is the Payload Format indicator. If present and set to 1, this
indicates that the PUBLISH payload is UTF-8 encoded data. If set to 0, or if
the indicator is not present then the payload is an unspecified byte format,
exactly as with MQTT v3.1.1.

# Publication Expiry interval

This is an identifier/value pair for use when publishing. If present, this
value is a 4 byte integer which gives the number of seconds for which the
server will attempt to deliver this message to a subscriber. This means that an
offline client with messages being queued may not receive all of the messages
when it reconnects, due to some of them expiring. Interestingly, when the
server does deliver a message that had a Publication Expiry set, it sets the
Publication Expiry on the outgoing message to the client but with the amount of
time that there is left until the message expires. This means that the true
time to expiry will propagate through bridges or similar.

# Publish Return Codes

The PUBACK and PUBREC packets have a new entry in their variable header which
is the Publish Return Code. This can be used to tell the client a message has
been refused for various reasons, accepted, or accepted with no matching
subscribers.  For the PUBREC packet, if the message is refused or accepted with
no matching subscribers then there is no expectation for the PUBREL/PUBCOMP
messages to be sent for that message.

The PUBCOMP packet also has a similar entry which has the same set of return
codes and an additional one for the case when a message had expired. This is
for the case when a client reconnects with clean start set to 0 and it has a
QoS 2 message part way through its handshake, but the server has already
expired the message.

There is still no way to tell a client that its QoS 0 message was refused.

# Disconnect notification

In MQTT v3.1.1 and before, only the client sends a DISCONNECT packet. In the
draft spec, either the client or the server can send DISCONNECT and it is used
to indicate a reason for disconnection. The disconnect return codes are:

 * 0: Connection disconnected by application (sent by client)
 * 1: Server temporarily unavailable (server)
 * 2: Server unavailable (server)
 * 3: Malformed UNSUBSCRIBE packet received (server)
 * 4: Session taken over (server - for when another client connects with the same ID)
 * 5: Malformed packet received

It is clear that there is some duplication there, so I think this is a likely
place that changes will be made.

# Disconnect expiry notification

The DISCONNECT packet can also include a Session Expiry interval value, as with
CONNECT. This allows a client to clean up when it disconnects, or to set a long
expiry time, even if these were not specified at the initial connect.

[MQTT Technical Committee]: https://www.oasis-open.org/committees/tc_home.php?wg_abbrev=mqtt
