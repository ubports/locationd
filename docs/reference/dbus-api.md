---
title: "DBus API"
table_of_contents: True
---

# DBus API

The locationd service comes with an extensive DBus API interface which
allows to interact with the service in various ways. It covers the following
use cases:

  * Obtain location data
  * Register as an out-of-tree location provider

!!! Note:
    All types described in this document refer to DBus types. Please
    see the [DBus specification](https://dbus.freedesktop.org/doc/dbus-specification.html) for details.

If you want to generate your own DBus wrapper automatically with a tool
like `gdbus-codegen` you can use the available introspection files from
[here](https://git.launchpad.net/~snappy-hwe-team/snappy-hwe-snaps/+git/location-service/tree/data/location/dbus).

## Object structure

The service exposes a central DBus object at the path `/core/locationd/Service`

Session objects are available on paths selected by the service when a
session is created via the `CreationSessionForCriteria` method from the
`core.locationd.Service` interface.

## Available interfaces

The main interface used to communicate with the service is `core.locationd.Service`. It
gives a client control to create a new session to listen for position
updates or to register a provider which can deliver additional position
updates to the service.

### core.locationd.Service

### Methods

**ObjectPath CreateSessionForCriteria(requirements a{sv})**

Creates a new session for monitoring updates delivered by the
service. Returns a path to an object implementing
`core.locationd.Session.Service` on success, an error otherwise.

The following keys for the `requirements` argument are handled by the service:

 * wants-position (Type: `b`)
 * wants-heading (Type: `b`)
 * wants-velocity (Type: `b`)
 * horizontal-accuracy (Type: `d`, in [m])
 * vertical-accuracy (Type: `d`, in [m])
 * velocity-accuracy (Type: `d`, in [m/s])
 * heading-accuracy: (Type: `d`, in [°])

**void AddProvider(object ObjectPath)**

Registers 'object' implementing the core.locationd.Service.Provider interface with the service. Returns an error in case of issues.

**void RemoveObject(object ObjectPath)**

Removes 'object' implementing core.locationd.Service.Provider
from the service.

### Properties

**State**

Type: `s`

Access: read

The current state of the service. Possible values are

 * disabled
 * enabled
 * active

**DoesSatelliteBasedPositioning**

Type: `b`

Access: read

Indicates whether the service considers providers relying on satellite
constellation for positioning requests.

**DoesReportCellAndWifiIds**

Type: `b`

Access: read

Indicates whether the service honors location data from providers that
use cell towers or WiFi networks to provide location data.

**IsOnline**

Type: `b`

Access: read

Indicates whether the positioning engine powering the service
is online or not.

**VisibleSpaceVehicles**

Type: `aa{sv}`

Access: read

Within every dict, at least the following keys are available:

 * type: string
 * id: int32
 * snr: double
 * has-almanac-data: boolean
 * has-ephimeris-data: boolean
 * used-in-fix: boolean
 * azimuth: double
 * elevation: double

### core.locationd.Session

### Methods

**void StartPositionUpdates()**

Requests the session to start delivering updates to Position

**void StopPositionUpdates()**

Requests the session to stop delivering updates to Position

**void StartVelocityUpdates()**

Requests the session to start delivering updates to Velocity.

**void StopVelocityUpdates()**

Requests the session to stop delivering updates to Velocity.

**void StartHeadingUpdates()**

Requests the session to start delivering updates to Heading.

**void StopHeadingUpdates()**

Requests the session to stop delivering updates to Heading.

### Properties

**Position**

Type: `(ta{sv})`

Access: read

Timestamped updates of position. Clock refers to unix time in
microseconds. The following keys are always available in the
dictionary:

 * latitude: double, in [°]
 * longitude: double, in [°]

The following keys are optional:

 * horizontal-accuracy: double, in [m]
 * altitude: double, in [m]
 * vertical-accuracy: double, in [m]

**Velocity**

Type: `(t(d))`

Access: read

Timestamped updates to the current velocity in [m/s]. Clock refers to unix time in microseconds.

**Heading**

Type: `(t(d))`

Access: read

Timestamped updates to the current heading in [°]. Clock refers to unix time in microseconds.
