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

## Example: count users with logind and utmp as fallback

In this example, we check at first if systemd-logind is running. If yes, we prefer this, else we will fallback to utmp.

```
int
count_users(void)
{
  int numuser = 0;
  struct utmp *ut;

  if (sd_booted() > 0) {
    numuser = sd_get_sessions(NULL);
  } else {
    setutent();
    while ((ut = getutent())) {
      if ((ut->ut_type == USER_PROCESS) && (ut->ut_name[0] != '\0'))
        numuser++;
    }
    endutent();
  }
  return numuser;
}
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
| ut_host | sd_session_get_remote_host() ||
| ut_exit | - ||
| ut_session | - ||
| ut_tv | sd_session_get_start_time()[^1] |Start time of the session, this could be earlier than the login of the user. |
| ut_addr_v6| - | See ut_host |

[^1]: only available with systemd v254 or later

## Determine boot time

Since the boot time is not available from `logind`, we need to find another source for this. There is not the one solution.

### Use CLOCK_BOOTTIME

The result is very exact, as long as this is not running in a VM, which got saved and restored later:

```
  struct timespec ts_now;
  struct timespec ts_boot;
  clock_gettime (CLOCK_REALTIME, &ts_now);
  clock_gettime (CLOCK_BOOTTIME, &ts_boot);
  struct timespec diff = {.tv_sec = ts_now.tv_sec - ts_boot.tv_sec,
                         .tv_nsec = ts_now.tv_nsec - ts_boot.tv_nsec};
  if (diff.tv_nsec < 0) {
          diff.tv_nsec += 1000000000; // nsec/sec
	  diff.tv_sec--;
  }
  time_t boottime = diff.tv_sec;
```

### Use time of file created during boot

Use the time of a file created during the boot phase,
e.g. `/var/lib/systemd/random-seed`.

Problem is, that this file will be created a random time after the boot process started.

### Use wtmpdb

[wtmpdb](https://github.com/thkukuk/wtmpdb) stores the boot time calculated with help of CLOCK_BOOTTIME during the boot process. Since it is unlikely, that a VM will be saved to disk during the boot process already, it should be very exact and reliable.

### Own service

Create a service, which stores the timestamp of boot into a file like `/run/boottime`.
