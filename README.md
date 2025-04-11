# Making utmp/wtmp Y2038 fit

Please read [Y2038](Y2038.md) for more information about why utmp/wtmp/btmp/lastlog uses 32bit time_t even on 64bit systems.

This repository contains the document with all background informations and patches for several packages.

## Documentation

* [Y2038 and utmp/wtmp/lastlog on bi-arch systems like x86-64](Y2038.md)
* [Mapping of struct utmp to libsystemd functions](utmp-to-logind.md)

## Debug utilitiy

[logindump](logindump) is a debug utility which dumps the data from `systemd-logind`, `wtmpdb`, `utmp` and `wtmp`.

## Patches
Packages for which patches exist:
* [coreutils](patches/coreutils/)
* [monitoring-plugins](patches/monitoring-plugins/)
* [net-snmp](patches/net-snmp/)
* [openssh](patches/openssh/)
* [procps-ng (3.3.17/4.0.3)](patches/procps-ng/)
* [psutil](patches/psutil/)
* [rsyslog](patches/rsyslog/)
* [samba](patches/samba/)
* [util-linux](patches/util-linux/)
