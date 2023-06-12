# procps-ng patches

This directory contains patches for procps-ng to use `systemd-logind` instead of `utmp` for uptime and w.

Upstream status:
* uptime: got already merged
* [w](https://www.freelists.org/post/procps/RFC-w-using-logind-instead-of-utmp)

List of patches:
* procps-ng-3.3.17-logind.patch - for procps-ng 3.3.17
* procps-ng-4.0.3-logind.patch - for procps-ng 4.0.3

To enable systemd support, you need:

* systemd >= v254 (or current git)
* apply the patch for the corresponding procps-ng version
* `./configure --with-systemd`
* `make`
