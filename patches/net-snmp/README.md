# net-snmp patches

This directory contains patches for net-snmp to use `systemd-logind` instead of `utmp` for count_users.

List of patches:
* [net-snmp-5.9.3-systemd-no-utmp.patch](net-snmp-5.9.3-systemd-no-utmp.patch)

To enable systemd support, you need:

* libsystemd and header files installed
* apply the patch 
* `./configure --with-systemd`
* `make`
