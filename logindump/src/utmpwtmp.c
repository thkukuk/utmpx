/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "config.h"

#include <time.h>
#include <utmp.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include <arpa/inet.h>

#include "logindump.h"
#include "basics.h"

static int
dump_utmp(const char *utmpfile)
{
  struct utmp *ut;
  int r;

  printf("Type PID      line           id     user       host                   addr              time                       session\n");

  if (utmpfile)
    {
      r = utmpname(utmpfile);
      if (r < 0)
	return r;
    }

  setutent();
  while ((ut = getutent()))
    {
      const char *addr_string;
      char buffer[INET6_ADDRSTRLEN];
      _cleanup_free_ char *time_string = NULL;

      if (ut->ut_addr_v6[1] || ut->ut_addr_v6[2] || ut->ut_addr_v6[3])
        addr_string = inet_ntop(AF_INET6, &(ut->ut_addr_v6), buffer, sizeof(buffer));
      else
        addr_string = inet_ntop(AF_INET, &(ut->ut_addr_v6), buffer, sizeof(buffer));

      if (format_time(ut->ut_tv.tv_sec, &time_string) < 0)
	oom();

      /*      type  pid    line     id       user     host     addr    time session */
      printf("[%d]  [%06d] [%-*.*s] [%-4.4s] [%-*.*s] [%-*.*s] [%-15s] [%s] [%i]\n",
	     ut->ut_type,
	     ut->ut_pid,
	     12, (int)sizeof(ut->ut_line), ut->ut_line,
	     ut->ut_id,
	     8, (int)sizeof(ut->ut_user), ut->ut_user,
	     20, (int)sizeof(ut->ut_host), ut->ut_host,
	     addr_string, time_string, ut->ut_session);
    }
  endutent();

  return 0;
}

int
main_utmp(int argc, char **argv, const char *default_input)
{
  struct option const longopts[] = {
    {"input", required_argument, NULL, 'i'},
    {NULL, 0, NULL, '\0'}
  };
  int c;
  const char *input = default_input;

  while ((c = getopt_long(argc, argv, "i:", longopts, NULL)) != -1)
    {
      switch(c)
        {
	case 'i':
          input = optarg;
          break;
        default:
          usage(EXIT_FAILURE);
          break;
        }
    }

  if (argc > optind)
    {
      fprintf(stderr, "Unexpected argument: %s\n", argv[optind]);
      usage(EXIT_FAILURE);
    }

  dump_utmp(input);

  return EXIT_SUCCESS;
}
