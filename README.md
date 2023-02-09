# Y2038 and utmp/wtmp/lastlog on bi-arch systems like x86-64

For background on the Y2038 problem (32bit time_t counter will overflow) I suggest to start with the wikipedia [Year 2038 problem](https://en.wikipedia.org/wiki/Year_2038_problem) article.

The general statement so far has always been that on 64bit systems with a 64bit time_t you are safe with respect to the Y2038 problem.
But this doesn't seem to be correct: on bi-arch systems like x86-64 (so which can execute 64bit and 32bit binaries) glibc defines `__WORDSIZE_TIME64_COMPAT32`, which leads to the fact, that `struct lastlog` and `struct utmp` uses **int32_t** instead of **time_t**. So we have a Y2038 problem, which is not easy fixable, as this would require ABI and on disk format changes.

Affected is everything, which includes `utmp.h`, `lastlog.h`, accesses [/run/utmp](https://manpages.opensuse.org/utmp.5) or [/var/log/wtmp](https://manpages.opensuse.org/wtmp.5) or uses the following functions from glibc:
* [login()](https://manpages.opensuse.org/login.3) (ABI breakage)
* [logout()](https://manpages.opensuse.org/logout.3) (internal only)
* [updwtmp()](https://manpages.opensuse.org/updwtmp.3) (ABI breakage, WTMP file name)
* [utmpname()](https://manpages.opensuse.org/utmpname.3) (UTMP file name/_PATH_UTMP)
* [getutent()](https://manpages.opensuse.org/getutent.3) (ABI breakage)
* [getutid()](https://manpages.opensuse.org/getutid.3) (ABI breakage)
* [getutline()](https://manpages.opensuse.org/getutline.3) (ABI breakage)
* [pututline()](https://manpages.opensuse.org/pututline.3) (ABI breakage)
* [getutent_r()](https://manpages.opensuse.org/getutent_r.3) (ABI breakage)
* [getutid_r()](https://manpages.opensuse.org/getutid_r.3) (ABI breakage)
* [getutline_r()](https://manpages.opensuse.org/getutline_r.3) (ABI breakage)

Safe functions from `utmp.h`:
* [login_tty()](https://manpages.opensuse.org/login_tty.3)
* [setutent()](https://manpages.opensuse.org/setutent.3)
* [logwtmp()](https://manpages.opensuse.org/logwtmp.3)
* [endutent()](https://manpages.opensuse.org/endutent.3)

Paths which may need to be changed, to have the old utmp/wtmp/btmp/lastlog and new in parallel (all defined in `paths.h`:
* _PATH_WTMP `/var/log/wtmp`
* _PATH_UTMP `/var/run/utmp`
* _PATH_LASTLOG `/var/log/lastlog`

Unknown location:
* _PATH_BTMP `/var/log/btmp`

The following projects are affected:

* [systemd](https://github.com/systemd/systemd)
  * Includes `utmp.h` and `utmpx.h` in several places, but it's not clear if it is really using it
* [Linux-PAM](https://github.com/linux-pam/linux-pam)





Beside the background informations will this repository contain libutmp, a PoC to  solve the Y2038 (32bit time_t) problems with utmp/wtmp/lastlog on bi-archs.
