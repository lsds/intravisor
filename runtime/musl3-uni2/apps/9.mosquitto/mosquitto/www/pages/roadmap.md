<!--
.. title: Roadmap
.. slug: roadmap
.. date: 2018-11-09 10:53:50 UTC
.. tags:
.. category:
.. link:
.. description:
.. type: text
-->

# Roadmap

## Version 1.6

The next minor release. The focus of this release is on providing support for
version 5 of the MQTT protocol.

This release will provide a feature complete implementation, but does not
represent the final interface for all features. In particular, functions are
being added to libmosquitto to provide support for MQTT 5 features, but these
will be consolidated with the API changes planned for version 2.0.

### Deprecation notices

#### libmosquittopp

libmosquittopp, the C++ wrapper around libmosquitto is now deprecated and will
be removed in the next major release (2.0). The wrapper came about by an
external request and at the time it was created there were no other C++
solutions for MQTT. This has changed in the past years and this wrapper
provides no benefit over true C++ libraries or using the pure C libmosquitto.

#### libmosquitto API changes

The Mosquitto project has maintained API and ABI compatibility in libmosquitto
since version 1.0, and has dealt with the introduction of new specification
features by adding new functions which duplicate the behaviour of existing
functions, but with additional arguments to support the new features.
Particularly with regards to adding support for MQTT version 5, this has lead
to a proliferation of functions which offer small variations on a theme.

The libmosquitto functions listed below (which includes some new functions
included in 1.6) are going to be updated for version 2.0. Functions not listed
here should still be considered at risk of being updated.

* mosquitto\_will\_set
* mosquitto\_connect\*
* mosquitto\_reconnect\*
* mosquitto\_disconnect
* mosquitto\_publish\*
* mosquitto\_subscribe\*
* mosquitto\_unsubscribe\*
* mosquitto\_loop\*
* mosquitto\_\*\_callback\_set
* All callbacks
* mosquitto\_\*\_topic\_check\*


## Version 2.0

This is the next major release and includes breaking changes. Other features
planned include:

## Disk persistence improvements

A new disk persistence interface will be created to allow persistence to occur
immediately, rather than periodically. This will allow queued messages for
disconnected clients to be removed from memory, and reduce the periodic pause
caused when writing the persistence file.

## Breaking changes

### libmosquitto

The libmosquitto API is being consolidated to better support the new MQTT 5
features whilst reducing the number of function variants.

### libmosquittopp

The C++ wrapper around libmosquitto will be removed in this release.
