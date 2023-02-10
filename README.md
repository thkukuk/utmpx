# utmp/wtmp always with 64bit time_t

Please read [Y2038](Y2038.md) for more information about why utmp/wtmp/btmp/lastlog uses 32bit time_t even on 64bit systems.

# libutmpx

libutmpx will become a PoC to solve the Y2038 (32bit time_t) problems with utmp and wtmp on bi-archs, if this files are really still needed and there is not a better solution.
