---
title: "Connect serial ports"
table_of_contents: False
---

# Connect serial ports

The `locationd:ubx` plug is using the `serial-port` interface to
give locationd access to the serial port being used to talk to the
GPS chipset. As the path to the serial port to use is hardware
specific the gadget snap needs to offer a slot based on the
`serial-port` interface the `locationd:ubx` plug can be connected to.

Auto connection of the `locationd:ubx` plug to a slot owned by
gagdet snap needs to be implemented by a snap-declaration assertion
based on the gadget snap and can't be offered from the locationd
snap itself.


Next to connecting a serial port through a snap slot you
also have to set the path for through the provider configuration. See
the [configuration reference](reference/configuration.md) for details.
For the the `ubx` provider this looks like this:

```bash
$ snap set locationd ubx.provider.device /dev/ttyACM1
```

## Example

A possible slot definition inside a gadget snap can look like this:

```bash
name: my-gadget
[...]
slots:
  ubx:
    interface: serial-port
    path: /dev/ttyACM1
```

The slot inside the gadget can then be manually connected to the
`ubx` plug of the locationd snap with the following command:

```
$ snap connect locationd:ubx my-gagdet:ubx
```

Afterwards the locationd snap has access to the serial port available
on `/dev/ttyACM1` and can use it to talk to the GPS chipset.