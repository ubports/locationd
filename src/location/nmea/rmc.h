// Copyright (C) 2016 Thomas Voss <thomas.voss.bochum@gmail.com>
//
// This library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef LOCATION_NMEA_RMC_H_
#define LOCATION_NMEA_RMC_H_

#include <location/nmea/cardinal_direction.h>
#include <location/nmea/date.h>
#include <location/nmea/latitude.h>
#include <location/nmea/longitude.h>
#include <location/nmea/mode.h>
#include <location/nmea/status.h>
#include <location/nmea/talker.h>
#include <location/nmea/utc.h>

#include <boost/optional.hpp>

#include <cstdint>

#include <vector>

namespace location
{
namespace nmea
{

/// @brief Recommended Minimum data.
///
/// The recommended minimum sentence defined by NMEA for GNSS system data.
struct Rmc
{
    Talker talker;
    boost::optional<Utc> utc;
    boost::optional<Status> status;
    boost::optional<Latitude> latitude;
    boost::optional<CardinalDirection> latitude_direction;
    boost::optional<Longitude> longitude;
    boost::optional<CardinalDirection> longitude_direction;
    boost::optional<float> speed_over_ground;  // [knots]
    boost::optional<float> course_over_ground; // [°]
    boost::optional<Date> date;
    boost::optional<float> magnetic_variation; // [°]
    boost::optional<CardinalDirection> cardinal_direction;
    boost::optional<Mode> mode;
};

}
}

#endif // LOCATION_NMEA_RMC_H_
