# coreutils patches

This directory contains patches for `pinky`, `uptime`, `users` and `who` of coreutils to use `systemd-logind` instead of `utmp`. They will become obsolete after Gnulib has support for logind.

Upstream:
Upstream will create a Gnulib wrapper for utmp using logind:
["who" reports funny dates](https://debbugs.gnu.org/cgi/bugreport.cgi?bug=64937)

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
