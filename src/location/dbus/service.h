/*
 * Copyright © 2012-2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Thomas Voß <thomas.voss@canonical.com>
 */
#ifndef LOCATION_DBUS_SERVICE_H_
#define LOCATION_DBUS_SERVICE_H_

#include <location/service.h>
#include <location/space_vehicle.h>

namespace location
{
namespace dbus
{

struct Service
{
    static constexpr const char* name()
    {
        return "core.locationd.Service";
    }

    static constexpr const char* path()
    {
        return "/core/locationd/Service";
    }
  };

}  // namespace dbus
}  // namespace location

#endif // LOCATION_DBUS_SERVICE_H_
