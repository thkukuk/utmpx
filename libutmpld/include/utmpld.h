/* Copyright (c) 2023 Thorsten Kukuk
   Author: Thorsten Kukuk <kukuk@suse.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>. */

#ifndef _UTMPLD_H_
#define _UTMPLD_H_

#include <stdint.h>

struct utmpld
{
  char *session_id;
  char *session_type;
  uid_t user_id;
  char *user_name;
  char *tty;
  char *display;
  unsigned int vtnr;
  char *remote_user;
  char *remote_host;
  uint64_t login_time; /* usec */
};

extern int utmpld_get_session_id (char **id);
extern int utmpld_set_tty (const char *id, const char *tty);

#endif /* _UTMPLD_H_ */
