# Y2038 and utmp/wtmp/lastlog on bi-arch systems like x86-64

For background on the Y2038 problem (32bit time_t counter will overflow) I suggest to start with the wikipedia [Year 2038 problem](https://en.wikipedia.org/wiki/Year_2038_problem) article.

The general statement so far has always been that on 64bit systems with a 64bit time_t you are safe with respect to the Y2038 problem.
But this doesn't seem to be correct: on bi-arch systems like x86-64 (so which can execute 64bit and 32bit binaries) glibc defines `__WORDSIZE_TIME64_COMPAT32`, which leads to the fact, that `struct lastlog` and `struct utmp` uses **int32_t** instead of **time_t**. So we have a Y2038 problem, which is not easy fixable, as this would require ABI and on disk format changes.

Affected is everything, which includes `utmp.h`, `utmpx.h`, `lastlog.h` accesses [/run/utmp](https://manpages.opensuse.org/utmp.5), [/var/log/wtmp](https://manpages.opensuse.org/wtmp.5), [/var/log/btmp](https://manpages.opensuse.org/lastb.1) or uses the following functions from glibc:
* [getutent()](https://manpages.opensuse.org/getutent.3) (ABI breakage)
* [getutent_r()](https://manpages.opensuse.org/getutent_r.3) (ABI breakage)
* [getutxent()](https://manpages.opensuse.org/getutxent.3) (ABI breakage)
* [getutid()](https://manpages.opensuse.org/getutid.3) (ABI breakage)
* [getutid_r()](https://manpages.opensuse.org/getutid_r.3) (ABI breakage)
* [getutxid()](https://manpages.opensuse.org/getutxid.3) (ABI breakage)
* [getutline()](https://manpages.opensuse.org/getutline.3) (ABI breakage)
* [getutline_r()](https://manpages.opensuse.org/getutline_r.3) (ABI breakage)
* [getutxline()](https://manpages.opensuse.org/getutxline.3) (ABI breakage)
* [getutmp()](https://manpages.opensuse.org/getutmp.3) (ABI breakage)
* [getutmpx()](https://manpages.opensuse.org/getutmpx.3) (ABI breakage)
* [login()](https://manpages.opensuse.org/login.3) (ABI breakage)
* [pututline()](https://manpages.opensuse.org/pututline.3) (ABI breakage)
* [pututxline()](https://manpages.opensuse.org/pututxline.3) (ABI breakage)
* [updwtmp()](https://manpages.opensuse.org/updwtmp.3) (ABI breakage, WTMP file name)
* [updwtmpx()](https://manpages.opensuse.org/updwtmpx.3) (ABI breakage, WTMPX file name)
* [utmpname()](https://manpages.opensuse.org/utmpname.3) (UTMP file name/_PATH_UTMP)
* [utmpxname()](https://manpages.opensuse.org/utmpxname.3) (UTMPX file name/_PATH_UTMPX)

Safe functions from `utmp.h`:
* [endutent()](https://manpages.opensuse.org/endutent.3)
* [endutxent()](https://manpages.opensuse.org/endutxent.3)
* [login_tty()](https://manpages.opensuse.org/login_tty.3)
* [logout()](https://manpages.opensuse.org/logout.3)
* [logwtmp()](https://manpages.opensuse.org/logwtmp.3)
* [setutent()](https://manpages.opensuse.org/setutent.3)
* [setutxent()](https://manpages.opensuse.org/setutxent.3)

Paths which may need to be changed, to have the old utmp/wtmp/btmp/lastlog and new in parallel (all defined in `paths.h`:
* UTMPX_FILE `/var/run/utmp`
* UTMPX_FILENAME `/var/run/utmp`
* WTMPX_FILE `/var/log/wtmp`
* WTMPX_FILENAME `/var/log/wtmp`
* _PATH_LASTLOG `/var/log/lastlog`
* _PATH_UTMP `/var/run/utmp`
* _PATH_UTMPX `/var/run/utmp`
* _PATH_WTMP `/var/log/wtmp`
* _PATH_WTMPX `/var/log/wtmp`

Unknown location:
* _PATH_BTMP `/var/log/btmp`

The following projects are affected:

* [systemd](https://github.com/systemd/systemd)
  * Includes `utmp.h` and `utmpx.h` in several places, but it's not clear if it is really using it
* [Linux-PAM](https://github.com/linux-pam/linux-pam)





Beside the background informations will this repository contain libutmp, a PoC to  solve the Y2038 (32bit time_t) problems with utmp/wtmp/lastlog on bi-archs.
