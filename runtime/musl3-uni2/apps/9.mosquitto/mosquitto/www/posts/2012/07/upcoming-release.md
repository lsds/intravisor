<!--
.. title: Upcoming release
.. slug: upcoming-release
.. date: 2012-07-21 09:17:21
.. tags: Testing
.. category:
.. link:
.. description:
.. type: text
-->

The next release of mosquitto is approaching. There is currently only one
feature left on the todo list to complete and I've pencilled in the end of the
month as the release date. The date may slip a week or two after that depending
on any bugs reported.

Despite the development being carried out in the 0.16 branch and the current
in-development version numbers being 0.15.90, this will be version 1.0 of
mosquitto. There has been significant API changes (now a lot more sane
hopefully) which means the client library interface version has been
incremented, and the number of changes involved in this release far outreach
any previous release, including SSL support, a pure Python client
implementation, a healthy start on tests and an associated improvement in
protocol compliance, and threaded client support. I think it is well worthy of
the version number.

I am, however, very keen that this be as bug free a release as possible. To
this end, if you're a mosquitto user I'd be very appreciative if you'd download
the current source code and give it a try. Maybe read through the documentation
and check it makes sense

The source for the current version is at either of these links (ignore the
"0.16", that is just the branch name):

 * <https://bitbucket.org/oojah/mosquitto/get/0.16.zip>
 * <https://bitbucket.org/oojah/mosquitto/get/0.16.bz2>

If you want to test but with a minimum amount of effort, please download the
source, run "make test" and report back any problems. This would be
particularly  useful if you are using something other than a
Debian/Ubuntu/openSUSE based Linux. If you have any problems, bugs can be
reported at <https://launchpad.net/mosquitto>, by leaving a comment or by
getting in touch directly. I'm interested in anything, but would be especially
keen to hear from you if you think something to do with the client API needs
changing.

Thanks in advance!
