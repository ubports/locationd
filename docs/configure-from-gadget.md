---
title: "Configure from gadget"
table_of_contents: True
---

# Configure from gadget

In order to provide a default configuration for the locationd snap
its configuration can be provided from a gadget snap.

The configuration items which can be configured from a gadget snap
are all listed [here](reference/configuration.md).

## Example

In order to configure the locationd snap from a gadget snap you need to 
explicitly add the items you want to set. Please see the
official [gadget snap documentation](https://docs.ubuntu.com/core/en/reference/gadget)
for more details on this.

As an example we're configuring the serial port to be used by the
`ubx` location provider and also enable the [AssistNow](https://www.u-blox.com/en/assistnow-lock-your-position-instantly)
feature u-blox chipsets offer.

!!! Note:
    You need an authentication token for [AssistNow](https://www.u-blox.com/en/assistnow-lock-your-position-instantly).
    Please see the [AssistNow documentation page](assistnow.md) for details.

```
defaults:
  # The id of the locationd snap as obtain by `snap info locationd`
  bUB8lXpOC3pItJMaJattT2jhDTyBWClE:
    ubx.provider.device: /dev/ttyACM1
    ubx.provider.protocol: ubx
    ubx.provider.assistnow.enable: true
    ubx.provider.assistnow.token: AABBCCDDEEFFGGHHII11223344
```

With this added to the gadget snap the locationd snap will be now
automatically configured when the device boots the first time and
all specified configuration items will be applied.

!!! Note:
    The configuration applied from the gagdet snap
    are pure defaults which are only set on first device boot. Updated
    configuration data for already deployed devices can not be applied
    this way.