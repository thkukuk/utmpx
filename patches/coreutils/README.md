# coreutils patches

This directory contains patches for `pinky`, `uptime`, `users` and `who` of coreutils to use `systemd-logind` instead of `utmp`.

List of patches:
* local.mk.diff - Hack to linky against libsystemd
* pinky.c.diff - Ready
* uptime.c.diff - Ready
* users.c.diff - Ready
* who.c.diff - Work In Progress

To enable systemd support, you need:

* systemd >= v254
* apply the patches
* enable "WITH_SYSTEMD": `echo "#define WITH_SYSTEMD 1" >> lib/config.h`
* `./configure`
* `make`
