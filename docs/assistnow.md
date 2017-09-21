---
title: "u-blox AssistNow"
table_of_contents: False
---

# u-blox AssistNow 

[AssistNow](https://www.u-blox.com/en/assistnow-lock-your-position-instantly)<sup
id="a1">[1](#f1)</sup> is a technology from u-blox which allows
instant locking of the current position. It is an implementation of Assisted GPS
(A-GPS).

!!! Note:
    The AssistNow technology is only available with chipsets from
    u-blox.

locationd comes with support for AssistNow but keeps it disabled by defaut as
it is a paid service. To be able to use it you need to obtain a license from
u-blox.

## Configure AssistNow Support

locationd makes it easy to enable support for AssistNow. For that you only
need the authentication token you get from u-blox. The only step necessary
to enable AssistNow is to set two configuration items:

```
$ snap set locationd ubx.provider.assistnow.enable=true
$ snap set locationd ubx.provider.assistnow.token=MYTOKEN
```

You need to replace `MYTOKEN` with the token you received from u-blox. After
applying both changes you're ready to use AssistNow.

Now the `ubx` provider inside locationd is successfully registered
to use the AssistNow service.

!!! Note:
    With the current version of the locationd snap you need to
    restart the backend service in order to let the service sync with the
    applied configuration changes. In a future version of the snap this
    will be automatically handled. You can restart the backend service with
    the following command: <br/><br/>
    ```$ sudo systemctl restart snap.locationd.run```

!!! Positive "Pro tip":
    If you want to provision a device from the first boot on
    with AssistNow enabled please have a look at [Configure from gadget](configure-from-gadget.md)
    for instructions of how to implement this.

<b id="f1">1</b> AssistNow is a registered trademark of [u-blox](https://u-blox.com) [↩](#a1)
