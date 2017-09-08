---
title: "Available Providers"
table_of_contents: True
---

# Available Providers

locationd comes with a set of builtin providers. Each provider will
retrieve positioning data from a source and hand it to the locationd
service which will forward it to its users.

This page lists all existing providers and gives necessary information.

!!! positive "Pro-tip":
    You can list all implemented providers with the `locationd.list-providers`
    command.

## dummy

A `dummy` provider which does nothing but returns dummy position data. It
is used for testing and validation and not of any use for anything else.

## fusion

The `fusion` provider combines positioning data from multiple providers
and returns the most suitable position. It follows the principle of
forwarding the neweest and most accurate position out of multiple
providers to the locationd engine.

## gps

The `gps` is a legacy provider which integrates locationd with a GPS
driver originating in a Android HAL implementation. It is not used
in the snap distribution of locationd but kept for reference and
possible future use cases.

## mls

The `mls` provider uses WiFi access points and WWAN Cell ids to feed
the [Mozilla Location Service](https://location.services.mozilla.com/)
and retrieve positioning data based on these.

It can interact with the `network-manager` or `wpa-supplicant` snaps
installed on the same system to find available WiFi access points but
does not yet integrate with the `modem-manager` snap to obtain the
current cell id.

## remote

The remote provider allows locationd to connect with out of process
providers which are implemented by other components in the system.

## sirf

The `sirf` provider implements support for the properietary SiRF
protocol used by GPS chipsets from SiRF Technology.

## ubx

The `ubx` provider implements support for the u-blox protocol used
by GPS chipsets from u-blox.