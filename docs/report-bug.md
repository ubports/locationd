---
title: "Report a Bug"
table_of_contents: False
---

# Rebort a Bug

Bugs can be reported [here](https://bugs.launchpad.net/snappy-hwe-snaps/+filebug).

When submitting a bug report, please attach system log coming from the journal:

 * $ journalctl --no-pager > system-log

!!! Warning:
    You just dumped the entire system log into a file. Before you upload it
    somewhere please scan it and verify it doesn't include any details you don't want
    to leak to the public.

And the output of the following two commands:

```
$ locationd.status
$ journalctl --no-pager -u snap.locationd.run
```
