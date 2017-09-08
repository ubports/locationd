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
    It might take a moment for first updates to appear as locationd
    keeps positioning only active when there is atleast a single user
    present. If the monitor command is the only active it needs to
    warum up the chip and lock the current positon first before it
    can come back with an update.

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
