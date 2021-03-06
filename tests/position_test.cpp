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
#include <location/position.h>

#include <gtest/gtest.h>

TEST(Position, AllFieldsAreInvalidForDefaultConstructor)
{
    location::Position p;
    EXPECT_FALSE(p.altitude());
    EXPECT_FALSE(p.accuracy().horizontal());
    EXPECT_FALSE(p.accuracy().vertical());
}

TEST(Position, InitWithLatLonGivesValidFieldsForLatLon)
{
    location::Position p{location::units::Degrees{0}, location::units::Degrees{0}};
    EXPECT_FALSE(p.altitude());
}

TEST(Position, InitWithLatLonAltGivesValidFieldsForLatLonAlt)
{
    location::Position p{}; p.altitude(4 * location::units::meters);
    EXPECT_TRUE(static_cast<bool>(p.altitude()));
}

#include <location/dbus/codec.h>
