# samba patches

This directory contains patches for `samba` to use `systemd-logind` instead of `utmp`.

List of patches:
* samba-utmp-logind.patch - `rpcd_classic` get's the list of logged in usernames from logind.

To enable logind support, you need:

* apply the patch
* `./configure --with-systemd --with-pam ...`
* `make`
