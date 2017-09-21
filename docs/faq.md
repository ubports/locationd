---
title: "FAQ"
table_of_contents: False
---

# FAQ

This section covers some of the most commonly encountered problems and attempts
to resolve them.

If this still doesn't help, feel free to file a [bug report](report-bug.md).

### Why do I not see any positioning data reported by the locationd.monitor command?

This can have multiple reasons:

 * *No suitable location provider configured:* At the moment locationd only loads the
   `ubx` location provider by default and needs to be configured with the correct
   serial port and necessary plugs/slots connected. Please see the documentation
   [here](connect-serial-ports.md) for more details.

 * *No device path for SiRF or u-blox provider configured:* Please have a look at the
   steps necessary to [connect serial ports](connect-serial-ports.md) with the
   locationd snap.

 * *Determining the initial location takes a while:* Depending on which provider is being
   used, determining the initial position may take some time. If `locationd.monitor` is the
   only client of locationd, there will be a delay before it starts providing location updates.

 * *No satellites visibile:* If the device is not able to see the minimum number of
   satellites (this number is four for GPS) due to being indoors, in a tunnel, or some
   other situation that blocks line of sight to satellites, then this will prevent the GPS
   from being able to determine its position.

## How can I enable support for Assisted GPS (A-GPS)?

At the moment only the `ubx` plugin for u-blox chipsets provides support
for A-GPS through the commercial [AssistNow](https://www.u-blox.com/en/assistnow-lock-your-position-instantly)
service from u-blox. You need to have a subscription from u-blox in order
to use it. Please see the [configuration](reference/configuration.md) part
of the documentation to find details about how to configure [AssistNow](https://www.u-blox.com/en/assistnow-lock-your-position-instantly)
it.
