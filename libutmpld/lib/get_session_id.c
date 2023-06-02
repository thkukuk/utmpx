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

#include <errno.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>

#include "utmpld.h"

#define DBUS_DESTINATION "org.freedesktop.login1"
#define DBUS_PATH "/org/freedesktop/login1/session/auto"
#define DBUS_INTERFACE "org.freedesktop.login1.Session"

int
utmpld_get_session_id (char **id)
{
  sd_bus *bus = NULL;
  sd_bus_error error = SD_BUS_ERROR_NULL;
  char *session_id = NULL;
  int r;

  if (id)
    *id = NULL;

  if ((r = sd_bus_open_system(&bus)) < 0)
    return r;

  if ((r = sd_bus_get_property_string(bus, DBUS_DESTINATION,
                                      DBUS_PATH, DBUS_INTERFACE,
                                      "Id", &error, &session_id)) < 0)
    return r;

  *id = session_id;

  return sd_bus_flush(bus);
}
