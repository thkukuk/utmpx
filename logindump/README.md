# logindump

`logindump` is a simple, small utility to dump the informations from `systemd-logind`, `utmp`, `wtmpdb` and `wtmp` for debugging purpose.

There is already `utmpdump` from util-linux, but this can only dump files in `utmp` format (so `/run/utmp` and `/var/log/wtmp`), but not the Y2038 ready replacements `systemd-logind` and `wtmpdb`.
