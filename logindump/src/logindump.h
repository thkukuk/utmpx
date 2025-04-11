//SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <time.h>

extern void oom(void);

extern void usage(int retval);

extern int main_logind(int argc, char **argv);
extern int main_wtmpdb(int argc, char **argv);
extern int main_utmp(int argc, char **argv, const char *def);

extern int format_time(time_t t, char **dst);
