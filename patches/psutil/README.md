# psutil patches

This directory contains patches for `psutil` to use `systemd-logind` instead of `utmp`.

Upstream PRs:
* [Use logind instead of utmp because of Y2038](https://github.com/giampaolo/psutil/pull/2300)


List of patches:
* logind.patch - get data from logind instead of utmp
