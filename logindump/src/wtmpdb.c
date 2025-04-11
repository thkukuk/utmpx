/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "config.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <limits.h>
#include <wtmpdb.h>

#include "basics.h"
#include "logindump.h"

int wflag = 0; /* XXX */

/* map "soft-reboot" to "s-reboot" if we have only 8 characters
   for user output (no -w specified) */
static const char *
map_soft_reboot(const char *user)
{
  if (wflag || !streq(user, "soft-reboot"))
    return user;

  return "s-reboot";
}

static int
print_entry (void *unused _unused_,
             int argc, char **argv, char **azColName)
{
  _cleanup_free_ char *login_str = NULL, *logout_str = NULL;
  char *endptr;

  /* ID, Type, User, LoginTime, LogoutTime, TTY, RemoteHost, Service */
  if (argc != 8)
    {
      fprintf (stderr, "Mangled entry:");
      for (int i = 0; i < argc; i++)
        fprintf (stderr, " %s=%s", azColName[i], strna(argv[i]));
      fprintf (stderr, "\n");
      exit (EXIT_FAILURE);
    }

  const char *id = argv[0];
  const char *type = argv[1];
  const char *user = argv[2];
  const char *tty = strempty(argv[5]);
  const char *host = strempty(argv[6]);
  const char *service = strempty(argv[7]);

  uint64_t login_t = strtoull(argv[3], &endptr, 10);
  if ((errno == ERANGE && login_t == ULLONG_MAX)
      || (endptr == argv[3]) || (*endptr != '\0'))
    fprintf (stderr, "Invalid numeric time entry for 'login': '%s'\n",
             argv[3]);

  uint64_t logout_t = 0;
  if (argv[4])
    {
      logout_t = strtoull(argv[4], &endptr, 10);
      if ((errno == ERANGE && logout_t == ULLONG_MAX)
          || (endptr == argv[4]) || (*endptr != '\0'))
        fprintf (stderr, "Invalid numeric time entry for 'logout': '%s'\n",
                 argv[4]);
    }

  if (format_time(login_t/USEC_PER_SEC, &login_str) < 0)
    oom();

  if (format_time(logout_t/USEC_PER_SEC, &logout_str) < 0)
    oom();

  /*      ID     type user   tty     host    service login logout*/
  printf("[%-6s] [%s] [%-8s] [%-12s] [%-16s] [%-12s] [%s] [%s]\n",
	 id, type, map_soft_reboot (user), tty, host,
	 service, login_str, logout_str);

  return 0;
}

static int
dump_wtmpdb(const char *input)
{
  _cleanup_free_ char *error = NULL;
  int r;

  printf("ID      type user       tty            host               service        login                      logout\n");


  r = wtmpdb_read_all (input, print_entry, &error);
  if (r < 0)
    {
      if (error)
	fprintf (stderr, "%s\n", error);
      else
        fprintf (stderr, "Couldn't read all wtmp entries\n");

      return r;
    }

  return 0;
}

int
main_wtmpdb(int argc, char **argv)
{
  struct option const longopts[] = {
    {"input", required_argument, NULL, 'i'},
    {NULL, 0, NULL, '\0'}
  };
  const char *input = NULL;
  int c, r;

  while ((c = getopt_long(argc, argv, "", longopts, NULL)) != -1)
    {
      switch (c)
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

  r = dump_wtmpdb(input);
  if (r < 0)
    {
      fprintf(stderr, "Error dumping wtmpdb data: %s\n", strerror(-r));
      exit(-r);
    }

  exit(EXIT_SUCCESS);
}
