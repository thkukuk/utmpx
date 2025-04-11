/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "config.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <paths.h>

#include "logindump.h"

int
format_time(time_t t, char **dst)
{
  assert(dst);

  if (asprintf(dst, "%s", ctime(&t)) < 0)
    return -ENOMEM;

  if (strlen(*dst) > 0)
    (*dst)[strlen(*dst)-1] = '\0'; /* Remove trailing '\n' */

  return 0;
}

void
oom(void)
{
  fputs("ERROR: running out of memory!\n", stderr);
  exit(EXIT_FAILURE);
}

void
usage(int retval)
{
  FILE *output = (retval != EXIT_SUCCESS) ? stderr : stdout;

  fputs("Usage: logindump [command] [options]\n", output);
  fputs("Commands: logind, wtmpdb, utmp, wtmp\n\n", output);

  fputs("logind - Get data from systemd-logind (default)\n", output);
  fputs("Options for logind:\n", output);
  fputs("\n", output);

  fputs("wtmpdb - Get data from wtmpdb file\n", output);
  fputs("Options for wtmp:\n", output);
  fputs("  -i, --input         Input file in wtmpdb format\n", output);
  fputs("\n", output);

  fputs("utmp - Get data from utmp file\n", output);
  fputs("Options for utmp:\n", output);
  fputs("  -i, --input         Input file in utmp format\n", output);
  fputs("\n", output);

  fputs("wtmp - Get data from wtmp file\n", output);
  fputs("Options for wtmp:\n", output);
  fputs("  -i, --input         Input file in utmp format\n", output);
  fputs("\n", output);

  fputs("Generic options:\n", output);
  fputs("  -h, --help          Display this help message and exit\n", output);
  fputs("  -v, --version       Print version number and exit\n", output);
  fputs("\n", output);
  exit(retval);
}

int
main(int argc, char **argv)
{
  struct option const longopts[] = {
    {"help",     no_argument,       NULL, 'h'},
    {"version",  no_argument,       NULL, 'v'},
    {NULL, 0, NULL, '\0'}
  };
  int c;

  if (argc == 1)
    return main_logind(argc, argv);
  else if (strcmp(argv[1], "logind") == 0)
    return main_logind(--argc, ++argv);
  else if (strcmp(argv[1], "wtmpdb") == 0)
    return main_wtmpdb(--argc, ++argv);
  else if (strcmp(argv[1], "utmp") == 0)
    return main_utmp(--argc, ++argv, NULL);
  else if (strcmp(argv[1], "wtmp") == 0)
    return main_utmp(--argc, ++argv, _PATH_WTMP);

  while ((c = getopt_long(argc, argv, "hv", longopts, NULL)) != -1)
    {
      switch (c)
	{
	case 'h':
	  usage(EXIT_SUCCESS);
	  break;
	case 'v':
	  printf("logindump %s\n", VERSION);
	  exit(EXIT_SUCCESS);
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

  exit(EXIT_SUCCESS);
}
