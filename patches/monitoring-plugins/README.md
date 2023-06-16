# monitoring-plugins patches

This directory contains patches for monitoring-plugins to use `systemd-logind` instead of `utmp` for check_users.

List of patches:
* systemd-not-utmp.patch

To enable systemd support, you need:

* libsystemd and header files installed
* apply the patch 
* `./configure`
* `make`
