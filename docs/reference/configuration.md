---
title: "Snap Configuration"
table_of_contents: False
---

# Snap Configuration

In parallel to its own configuration system the locationd snap provides a set of
snap configuration items which can be changed through the *snap set* system
command. These allow customization of the default behaviour of the locationd snap
from a device [gadget snap](https://docs.ubuntu.com/core/en/reference/gadget).

The available configuration items are documented in the following sections.

### ubx.provider.enable

This configuration item allows enabling or disabling the u-blox location
provider.

Possible values:

 * `true`: Enable the ubx provider
 * `false`: Disable the ubx provider

Default value: `true`

Example:

```
$ snap set locationd ubx.provider.enable=true
```

### ubx.provider.device

Path to serial port device which the locationd service will use to
communicate with the u-blox chipset.

Example:

```
$ snap set locationd ubx.provider.device=/dev/ttyACM1
```

### ubx.provider.protocol

Switch the provider implementation between using the u-blox or NMEA
protocol.

Possible values:

 * `ubx`: Use the `ubx` protocol to talk to the chipset
 * `nmea`: Use the standard NMEA protocol to talk to the chipset

Default value: `ubx`

Example:

```
$ snap set locationd ubx.provider.protocol=ubx
```

### ubx.provider.assistnow.enable

Enable or disable the [AssistNow](https://www.u-blox.com/en/assistnow-lock-your-position-instantly)
functionality a u-blox chipset provides. AssistNow is the assisted GPS impementation from u-blox.

Possible values:

 * `true`: Enable AssistNow functionality
 * `false`: Disable AssistNow functionality

Default value: `false`

Example:

```
$ snap set locationd ubx.provider.assistnow.enable=true
```

### ubx.provider.assistnow.token

Access token for the AssistNow service which is necessary to provide in order
to allow use of the service.

Default value: `empty`

Example:

```
$ snap set locationd ubx.provide.assistnow.token=aabbccddee
```

### sirf.provider.enable

This configuration item allows enabling or disabling the SiRF location
provider.

Possible values:

 * `true`: Enable the SiRF provider
 * `false`: Disable the SiRF provider

Default value: `true`

Example:

```
$ snap set locationd sirf.provider.enable=true
```

### sirf.provider.device

Path to serial port device which the locationd service will use to
communicate with the SiRF chipset.

Example:

```
$ snap set locationd sirf.provider.device=/dev/ttyACM1
```

### sirf.provider.protocol

Switch the provider implementation between using the SiRF or NMEA
protocol.

Possible values:

 * `sirf`: Use the `sirf` protocol to talk to the chipset.
 * `nmea`: Use the standard NMEA protocol to talk to the chipset.

Default value: `sirf`

Example:

```
$ snap set locationd sirf.provider.protocol=ubx
```

### mls.provider.enable

This configuration allows enabling or disabling the Mozilla Location Service provider.

As the location provider for the Mozilla Location Service will constantly talk to
a remote web service when enabled it is disabled by default to prevent the service
from talking to any web service without the user acknowledging this.

Default value: `false`

Possible values:

 * `true`: Enable the Mozilla Location Service provider
 * `false`: Disable the Mozilla Location Service provider

```
$ snap set locationd mls.provider.enable=true
```

### mls.provider.host

Host name or IP address of the [Mozilla Location Service](https://location.services.mozilla.com/).

Default value: `https://location.services.mozilla.com`

```
$ snap set locationd mls.provider.host=https://my.service
```

### mls.provider.api_key

API key to use with the [Mozilla Location Service](https://location.services.mozilla.com/). To be
allowed to use the [Mozilla Location Service](https://location.services.mozilla.com/) you need
to ask for a API key. See [here](https://location.services.mozilla.com/api) for details.

The default value is `test`, which limits the use of the service in some ways (not specified
by the [Mozilla Location Service](https://location.services.mozilla.com/)).

Default value: `test`

```
$ snap set locationd mls.provider.api_key=test
```
