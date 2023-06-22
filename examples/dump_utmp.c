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


/* This is a simple program dumping /run/utmp. Many saftey/security
   checks are missing, see this only as example, never use in production! */

#include <utmp.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

static void
format_time (char *dst, size_t dstlen, time_t t)
{
  snprintf (dst, dstlen, "%s", ctime (&t));
  dst[strlen (dst)-1] = '\0'; /* Remove trailing '\n' */
}

int
main (void)
{
  struct utmp *ut;

  printf("Type PID    line           id     user       host                   addr              time                       session\n");

  setutent ();
  while ((ut = getutent ()))
    {
      const char *addr_string;
      char buffer[INET6_ADDRSTRLEN];
      char time_string[40];

      if (ut->ut_addr_v6[1] || ut->ut_addr_v6[2] || ut->ut_addr_v6[3])
	addr_string = inet_ntop(AF_INET6, &(ut->ut_addr_v6), buffer, sizeof(buffer));
      else
	addr_string = inet_ntop(AF_INET, &(ut->ut_addr_v6), buffer, sizeof(buffer));

      format_time (time_string, sizeof (time_string), ut->ut_tv.tv_sec);


      /*      type pid    line     id       user     host     addr    time session */
      printf ("[%d] [%05d] [%-*.*s] [%-4.4s] [%-*.*s] [%-*.*s] [%-15s] [%s] [%i]\n",
	      ut->ut_type,
	      ut->ut_pid,
	      12, (int)sizeof(ut->ut_line), ut->ut_line,
	      ut->ut_id,
	      8, (int)sizeof(ut->ut_user), ut->ut_user,
	      20, (int)sizeof(ut->ut_host), ut->ut_host,
	      addr_string, time_string, ut->ut_session);
    }
  endutent ();

  return 0;
}
