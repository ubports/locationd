---
title: "Available Commands"
table_of_contents: True
---

# Available Commands

The locationd snap offers multiple commands which allow communication with
the locationd service daemon in multiple ways:

## locationd.list-providers

Lists all provider implementations known to the service.

!!! Positive "Pro tip": 
    This will only list implemented providers but don't tell if they are
    active or not.

Example:

```bash
$ locationd.list-providers
  - dummy::Provider
  - gps::Provider
  - mls::Provider
  - ubx::Provider
```

## locationd.status

Queries the status of a service instance.

Example:

```bash
$ locationd.status
  is online:                   true
  state:                       enabled
  satellite based positioning: true
  reports cell & wifi ids:     false
  svs:                         none
```

## locationd.monitor

Connects to a locationd instance and monitors its activity. Supports
KML or tabular data output of position/heading/velocity data.

!!! Note:
    There may be a short delay before positioning updates start to appear as locationd
    only reports updates if one or more clients are active. If the monitor command is the
    only client, this is the reason for the short delay. Also, locationd only reports
    updates if the device's location is actually changing. If the device is stationary,
    there will be no updates to report.

Example:

```bash
$ locationd.monitor
Enabled position/heading/velocity updates...
lat.[deg]      lon.[deg]      hor.acc.[m]    alt.[m]       ver.acc.[m]     heading[deg]   vel.[m/s]
51.44483       7.21064        13.27          n/a            n/a            n/a            n/a
51.44483       7.21064        13.26          n/a            n/a            n/a            n/a
51.44483       7.21069        16.36          n/a            n/a            n/a            n/a
[...]
```

## locationd.set

Adjust the configuration of the locationd service.

Example:

```bash
$ locationd.set --key=ubx.provider.path --value="/dev/ttyACM1"
```

See the [configuration documentation](configuration.md) for further details
and available options.
