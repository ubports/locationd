---
title: "Overview"
table_of_contents: True
---

# Overview

locationd is a system service which provides a multiplexing engine for one or
more location providers installed on the system. It provides a DBus API which
can be used by other applications or system services to control and/or monitor
positioning data.

## What locationd offers

The locationd snap offers the following features:

  * Support for GPS chipsets from SiRF and u-blox
  * Usage of the Mozilla Location Service database which allows location
    service based on network infrastructure like Bluetooth beacons, cell
    towers and WiFi access points
  * A specialized fusion provider which combines multiple location providers
    to find the most accurate position
  * Support for external location providers which are running on the same
    system an exposing a well defined DBus interface

## Learn more

Follow these links directly or use the menu on the left to learn more about
locationd and how to use it:

  * [Install locationd](installation.md)
  * [Obtain location from the service](obtain-location.md)
  * [Configure AssistNow support](assistnow.md)
