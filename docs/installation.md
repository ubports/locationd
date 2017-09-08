---
title: "Installation"
table_of_contents: True
---

# Installation

The snap can be installed from the Ubuntu Store with the following command

```
 $ snap install locationd
```

All relevant plugs of the locationd snap should be automatically connected:

```
$ snap interfaces locationd
Slot                       Plug
locationd:service-control  locationd:client-control
locationd:service-observe  locationd:client-observe
-                          locationd:network-manager
-                          locationd:ubx
```

!!! Note:
    The `locationd:network-manager` plug will be only connected if the
    network-manager snap was installed on the system.

    The `locationd:ubx` plug needs to be connected to a slot offering
    access to the serial port to be used by the `ubx` provider inside
    locationd. See the documentation [here](connect-serial-ports.md)
    for details.