# openssh patches

This directory contains patches for `sshd` from  to use `wtmpdb`.
Normally wtmpdb uses PAM, but for sshd this is not posssible, as the
name of the TTY is not known when PAM gets called.

List of patches:
* wtmpdb.diff - Adds wtmpdb support to sshd, configure and Makefile

To enable systemd support, you need:

* apply the patch
* `./configure --with-wtmpdb`
* `make`
