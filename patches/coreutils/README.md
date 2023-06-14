# coreutils patches

This directory contains patches for `pinky`, `uptime`, `users` and `who` of coreutils to use `systemd-logind` instead of `utmp`.

List of patches:
* pinky.patch
* uptime.patch 
* users.patch
* who.patch

To enable systemd support, you need:

* systemd >= v254
* apply the patches
* enable "WITH_SYSTEMD": `echo "#define WITH_SYSTEMD 1" >> lib/config.hin`
* `./configure`
* `make`
