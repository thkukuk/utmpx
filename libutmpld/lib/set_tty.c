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

// qdbus-qt5 --system org.freedesktop.login1 /org/freedesktop/login1/session/auto org.freedesktop.DBus.Properties.Get org.freedesktop.login1.Session Id

#define DBUS_DESTINATION "org.freedesktop.login1"
#define DBUS_PATH "/org/freedesktop/login1/session/%s"
#define DBUS_INTERFACE "org.freedesktop.login1.Session"

int
utmpld_set_tty (const char *id, const char *tty)
{
  sd_bus *bus = NULL;
  char *dbus_path;
  int r;

  if ((r = sd_bus_open_system(&bus)) < 0)
    return r;

  if (asprintf (&dbus_path, DBUS_PATH, id) < 0)
    return -ENOMEM;

  if ((r = sd_bus_call_method (bus, DBUS_DESTINATION, dbus_path,
                               DBUS_INTERFACE, "TakeControl", NULL, NULL,
			       "b", 1)) < 0)
    goto cleanup;

  if ((r = sd_bus_call_method(bus, DBUS_DESTINATION, dbus_path,
                              DBUS_INTERFACE, "SetTTY", NULL, NULL,
			      "s", tty)) < 0)
    goto cleanup;

  r = sd_bus_flush(bus);

 cleanup:
  free (dbus_path);
  return r;
}
