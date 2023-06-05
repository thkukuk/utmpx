# openssh patches

This directory contains patches for `sshd` to use `wtmpdb` and allows to tell systemd-logind/elogind the TTY.
Normally wtmpdb and systemd are using PAM, but for sshd this is not posssible, as the name of the TTY is not known when PAM gets called.

List of patches:
* wtmpdb.diff - Adds wtmpdb support to sshd, configure and Makefile
* logind-set-tty.patch - Adds support to sshd to tell systemd-logind/elogind the TTY

To enable wtmpdb and logind support, you need:

* apply the patches
* `./configure --with-wtmpdb --with-logind`
* `make`
