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

#ifndef UBX_8_MESSAGE_H_
#define UBX_8_MESSAGE_H_

#include <location/providers/ubx/_8/ack/ack.h>
#include <location/providers/ubx/_8/ack/nak.h>
#include <location/providers/ubx/_8/cfg/gnss.h>
#include <location/providers/ubx/_8/cfg/msg.h>
#include <location/providers/ubx/_8/cfg/rst.h>
#include <location/providers/ubx/_8/nav/pvt.h>
#include <location/providers/ubx/_8/nav/sat.h>

#include <boost/variant.hpp>

namespace location
{
namespace providers
{
namespace ubx
{
namespace _8
{

using Message = boost::variant<
    ack::Ack,
    ack::Nak,
    cfg::Gnss,
    cfg::Msg,
    cfg::Rst,
    nav::Pvt,
    nav::Sat
>;

}  // namespace _8
}  // namespace ubx
}  // namespace providers
}  // namespace location

#endif // UBX_8_MESSAGE_H_
