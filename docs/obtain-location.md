---
title: "Obtain Location"
table_of_contents: False
---

# Obtain Location

locationd offers a rich interface to allow clients to retrieve positioning data
of different kinds. Its API interface enables a user to specify what kind of
positioning he wants to retrieve and with which accuracy and update interval.

Internally locationd uses a so called `fusion` provider which aggregates the
position from multiple other providers to return the positioning data in the
requested accuracy, update interval etc. It will also pick the right set of
providers which fit the requested requirements.

## On the command line

The easiest way to obtain location data from the service is the `locationd.monitor`
command. It can report location data either in a table format on the
command line or formatted in [KML](https://en.wikipedia.org/wiki/Keyhole_Markup_Language).

To get the location continously reported in a table format you can run
the following command:

```
$ locationd.monitor --output-format=table
Enabled position/heading/velocity updates...
lat.[deg]      lon.[deg]      hor.acc.[m]    alt.[m]       ver.acc.[m]     heading[deg]   vel.[m/s]
51.44483       7.21064        13.27          n/a            n/a            n/a            n/a
51.44483       7.21064        13.26          n/a            n/a            n/a            n/a
51.44483       7.21069        16.36          n/a            n/a            n/a            n/a
[...]
```

The table header prints the used units for all values.

Alternatively if you want a continous stream of KML formatted positioning data:

```
$ locationd.monitor --output-format=kml
Enabled position/heading/velocity updates...
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<kml xmlns=\"http://www.opengis.net/kml/2.2\">
<Folder><open>1</open><name>Recorded positions</name>
<Placemark><name>1505125846423753112</name><Point><coordinates>7.21064,51.44483,0</coordinates></Point></Placemark>
</Folder></kml>
```

Please refer to the [official KML documentation](https://developers.google.com/kml/documentation/kmlreference)
about details of the KML format.

## In your application

The primary method applications should use to query location and/or receive
continual location updates is locationd's DBus API. It can be used to obtain
various information from the service including positioning data. The DBus
interface is described [here](reference/dbus-api.md).

The general steps to obtain location updates via DBus look like this:

 1. Create a new session with the service (`CreateSessionForCriteria`
    method of the `core.locationd.Service` interface) and specify
    which kind of updates the session should receive with the `requirements`
    parameter.
 2. Enable updates on the returned session object by calling the relevant
    methods (e.g. `StartPositionUpdates`)
 2. Register for property updates on the returned session objects and process
    any updates when received.

A very simple python based client application to retrieve just position
updates from the locationd service looks like this:

```
import sys
import dbus
from dbus.mainloop.glib import DBusGMainLoop
import gobject

dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
bus = dbus.SystemBus()

service = dbus.Interface(
  bus.get_object("core.locationd.Service", "/core/locationd/Service"),
  "core.locationd.Service")

requirements = dict()
# Sign up for position updates only. We're not interested in
# updates for heading or velocity.
requirements["wants-position"] = True
session_path = service.CreateSessionForCriteria(requirements)
if not session_path:
  print("ERROR: Failed to create session with locationd")
  sys.exit(1)

def session_properties_changed(properties):
  print("Got update from session:")
  for p in properties:
    print("%s = %s" % (p, properties[p]))

bus.add_signal_receiver(session_properties_changed,
                        path=session_path,
                        dbus_interface="core.locationd.Session",
                        signal_name="PropertyChanged")

session = dbus.Interface(
  bus.get_object("core.locationd.Service", session_path),
  "core.locationd.Session")
session.StartPositionUpdates()

gobject.MainLoop().run()
```
