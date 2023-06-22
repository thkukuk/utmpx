# Mapping of struct utmp to libsystemd functions

Every `utmp` entry is a struct which contains all informations about this session, while with systemd-logind (`libsystemd`) every single value needs to be fetched via a libsystemd function.

## Example for utmp

The traditional way to get all utmp records is:

```
struct utmp *u;
...
setutent();
while ((u = getutent())) {
        ... /* Parse struct utmp and use the data */
}
endutent();
```

## Example for libsystemd

With logind/libsystemd, this is a little bit different:

```
char **sessions_list;
int sessions = sd_get_sessions (&sessions_list);
...
for (int i = 0; i < sessions; i++) {
        const char *session_id = sessions_list[i];
        ... /* Fetch information for session ID */
	free (sessions_list[i]);
}
free (sessions_list);
```

## Mapping

An overview, which libsystemd function corresponds with which utmp entry
(session_id is one entry from the list retured by `sd_get_sessions`):

| struct utmp | libsystemd | comment |
|-------------|------------|---------|
| ut_type | - | Only `USER_PROCESS` is available|
| ut_pid  | sd_get_session_leader()[^1] ||
| ut_line | sd_get_session_tty() ||
| ut_id   | session_id |
| ut_user | sd_session_get_username()[^1] ||
| ut_host | sd_session_get_remote_host () ||
| ut_exit | - ||
| ut_session | - ||
| ut_tv | sd_session_get_start_time()[^1] ||
| ut_addr_v6| - | See ut_host |

[^1]: only available with systemd v254 or later

## Determine boot time

Since the boot time is not available from `logind`, we need to find another source for this. On Linux, this is really simple:

```
  struct timespec ts_now;
  struct timespec ts_boot;
  clock_gettime (CLOCK_REALTIME, &ts_now);
  clock_gettime (CLOCK_BOOTTIME, &ts_boot);
  time_t boottime = diff_timespec(&ts_now, &ts_boot);
```
