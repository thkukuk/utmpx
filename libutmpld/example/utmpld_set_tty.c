/* Copyright (c) 2023 Thorsten Kukuk
   Author: Thorsten Kukuk <kukuk@suse.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation in version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, see <http://www.gnu.org/licenses/>. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utmpld.h"

int
main (int argc, char *argv[])
{
  const char *tty;
  char *session_id;
  int r;

  if(argc != 2)
    {
      fprintf(stderr, "Usage: utmpld_set_tty <tty>\n");
      exit(1);
    }

  tty = argv[1];

  r = utmpld_get_session_id (&session_id);
  if (r < 0)
    {
      fprintf(stderr, "utmpld_get_id: %s\n", strerror(-r));
      return 1;
    }

  r = utmpld_set_tty (session_id, tty);
  if (r < 0)
    {
      fprintf(stderr, "utmpld_set_tty(%s, %s): %s\n",
	      session_id, tty, strerror(-r));
      return 1;
    }

  free (session_id);

  return 0;
}
