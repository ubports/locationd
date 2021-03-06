/*
 * Copyright © 2016 Canonical Ltd.
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

#include <location/serializing_bus.h>

std::shared_ptr<location::SerializingBus> location::SerializingBus::create()
{
    return std::shared_ptr<location::SerializingBus>{new location::SerializingBus{}};
}

location::SerializingBus::SerializingBus()
{
}

void location::SerializingBus::subscribe(const Event::Receiver::Ptr& receiver)
{

}

void location::SerializingBus::unsubscribe(const Event::Receiver::Ptr& receiver)
{
}

void location::SerializingBus::dispatch(const Event::Ptr& event)
{
}
