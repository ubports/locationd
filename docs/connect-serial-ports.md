---
title: "Connect serial ports"
table_of_contents: False
---

# Connect serial ports

The `locationd:ubx` plug uses the `serial-port` interface to
give locationd access to the serial port connected to the
GPS chipset. As the path to the serial port is hardware
specific, the gadget snap needs to offer a slot based on the
`serial-port` interface the `locationd:ubx` plug can be connected to.

Auto connection of the `locationd:ubx` plug to a slot owned by
gagdet snap needs to be implemented by a snap-declaration assertion
based on the gadget snap and can't be offered from the locationd
snap itself.

!!! Note:
    As of today (Sep 2017) it is not possible with Ubuntu Core
    to implement a snap-declaration assertion for a gadget snap
    which auto connects the necessary slots. An image needs to
    implement a custom systemd service job which calls `snap connect ..`
    to connect the right slots and plugs.

One the serial port plug and slot have been connected, the provider
still needs to be configured to use the device.  For example, you can
set the device path of the ubx provider via the following command:

```bash
$ snap set locationd ubx.provider.device /dev/ttyACM1
```

See the [configuration reference](reference/configuration.md) for more
details and further available configuration options.


## Example

The following is an example gadget snap slot definition for a GPS serial port:

```bash
name: my-gadget
[...]
slots:
  ubx:
    interface: serial-port
    path: /dev/ttyACM1
```

To manually connect this gadget snap serial port slot to locationd's serial-port
`ubx` plug, use the following command:

```
$ snap connect locationd:ubx my-gagdet:ubx
```

Once this interface connection has been made, locationd is allowed to access to
`/dev/ttyACM1`, and can communicate with the GPS chipset.
