# util-linux patches

This directory contains patches for util-linux to use `systemd-logind` instead of `utmp` and lastlog2 instead of lastlog.

Upstream PRs:
* [lslogins: Add support for lastlog2 (#2088)](https://github.com/util-linux/util-linux/pull/2164)
* [Y2038: query systemd-logind instead of utmp for username and tty (#2088)](https://github.com/util-linux/util-linux/pull/2100)

List of patches:
* lastlog2-support.patch
* use-logind-not-utmp.patch

To enable systemd support, you need:

* systemd >= v254 (or current git)
* apply the patches
* `./configure`
* `make`
