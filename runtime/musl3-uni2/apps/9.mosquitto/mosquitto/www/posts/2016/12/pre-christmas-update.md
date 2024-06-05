<!--
.. title: Pre Christmas Update
.. slug: pre-christmas-update
.. date: 2016-12-12 23:03:10
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

I have taken a bit of a break from Mosquitto for the past few months, partly
because I needed a break but also to work on another unrelated project. I'm now
back and working on Mosquitto again, primarily implementing support for the
upcoming MQTT v5 spec which has added even more features since I mentioned last
wrote about it. Once that is in a state that is reasonably compliant if
incomplete, I will be looking for testers.

There are a few fixes in the repository waiting for release, I anticipate
releasing 1.4.11 before the end of the year.

There have been some changes to test.mosquitto.org. On its original host I was
seeing lots of bandwidth being used by lots of clients, but in particular lots
and lots of tiny connections being made which not showing up on my bandwidth
monitoring, but were consuming bandwidth and causing problems at my provider.
My provider got in touch to say that at times approximately half of the network
flows for their network were related to test.mosquitto.org, and could would I
please have a chat with the transit provider to discuss how best to manage this
service. In the face of that and the risk of exceeding 2TB bandwidth usage per
month, test.mosquitto.org has been moved to a lower spec host with smaller
pipes and "automatic DDOS protection". This means I now get half a dozen emails
per day to say that test.mosquitto.org is under attack. If you find you can't
connect to test.mosquitto.org, it might be because you have been blocked by
this DDOS protection - if so, maybe think about how you are using the service.

The final thought for this post - if you are part of a company that uses
mosquitto and it adds value to your company, please consider making a
[donation] to the project that reflects that value. If it is difficult for your
company to make donations but you would still like to contribute back, please
get in touch and maybe we can arrange something.

[donation]: https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&amp;hosted_button_id=J66JWQ3N76L5A
