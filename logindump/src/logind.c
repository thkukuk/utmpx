/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "config.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <systemd/sd-login.h>

#include "logindump.h"
#include "strv.h"

typedef uint64_t usec_t;
#define USEC_PER_SEC  ((usec_t) 1000000ULL)

static int
dump_logind(void)
{
  _cleanup_strv_free_ char **sessions = NULL;
  int r;

  r = sd_get_sessions(&sessions);
  if (r <= 0)
    return r;

  r = 0;

  printf("Class     PID      line           id     user       host                   time\n");

  STRV_FOREACH(s, sessions)
    {
      _cleanup_free_ char *class = NULL, *tty = NULL, *name = NULL, *rhost = NULL;
      pid_t leader;
      usec_t start;
      char buf[30];
      int q;

      q = sd_session_get_class(*s, &class);
      if (q < 0)
	return q;

      q = sd_session_get_leader(*s, &leader);
      if (q < 0)
	return q;

      q = sd_session_get_tty(*s, &tty);
      if (q < 0 && q != -ENXIO && q != -ENODATA)
	return q;

      q = sd_session_get_username(*s, &name);
      if (q < 0)
	return q;

      q = sd_session_get_remote_host(*s, &rhost);
      if (q < 0 && q != -ENXIO && q != -ENODATA)
	return q;

      q = sd_session_get_start_time(*s, &start);
      if (q < 0)
	return q;

      const time_t t = start/USEC_PER_SEC;

      strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));

      /*      class  pid    line    id       user   host    time */
      printf("[%-7s] [%06d] [%-12s] [%-4.4s] [%-8s] [%-20s] [%s]\n",
	     class, leader, strempty(tty), *s,  name, strna(rhost), buf);
    }

  return r;
}

int
main_logind(int argc, char **argv)
{
  struct option const longopts[] = {
    {NULL, 0, NULL, '\0'}
  };
  int c, r;

  while ((c = getopt_long(argc, argv, "", longopts, NULL)) != -1)
    {
      switch (c)
        {
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

  r = dump_logind();
  if (r < 0)
    {
      fprintf(stderr, "Error dumping logind data: %s\n", strerror(-r));
      exit(-r);
    }

  exit(EXIT_SUCCESS);
}
