# procps-ng patches

This directory contains patches for procps-ng to use `systemd-logind` instead of `utmp` for uptime and w.

Upstream status:
* [uptime](https://gitlab.com/procps-ng/procps/-/commit/6d5d4d28040ca12d7ba673b7de0b62b0d7b9e9d0): Merged
* [w](https://gitlab.com/procps-ng/procps/-/merge_requests/203): Merged

List of patches:
* procps-ng-3.3.17-logind.patch - for procps-ng 3.3.17
* procps-ng-4.0.3-logind.patch - for procps-ng 4.0.3

To enable systemd support, you need:

* systemd >= v254
* apply the patch for the corresponding procps-ng version
* `./configure --with-systemd`
* `make`
