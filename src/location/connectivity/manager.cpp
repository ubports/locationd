/*
 * Copyright © 2012-2014 Canonical Ltd.
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

#include <location/connectivity/manager.h>
#include <location/connectivity/dummy_connectivity_manager.h>
#include "w11t_manager.h"
#include "ofono_nm_connectivity_manager.h"

#include <core/dbus/asio/executor.h>
#include <core/dbus/bus.h>

namespace connectivity = com::ubuntu::location::connectivity;
namespace w11t = location::connectivity::w11t;

std::ostream& connectivity::operator<<(std::ostream& out, connectivity::State state)
{
    switch (state)
    {
    case State::unknown: out << "State::unknown"; break;
    case State::asleep: out << "State::asleep"; break;
    case State::disconnected: out << "State::disconnected"; break;
    case State::disconnecting: out << "State::disconnecting"; break;
    case State::connecting: out << "State::connecting"; break;
    case State::connected_local: out << "State::connected_local"; break;
    case State::connected_site: out << "State::connected_site"; break;
    case State::connected_global: out << "State::connected_global"; break;
    }

    return out;
}

connectivity::Characteristics connectivity::operator|(connectivity::Characteristics l, connectivity::Characteristics r)
{
    return static_cast<connectivity::Characteristics>(static_cast<std::uint32_t>(l) | static_cast<std::uint32_t>(r));
}

connectivity::Characteristics connectivity::operator&(connectivity::Characteristics l, connectivity::Characteristics r)
{
    return static_cast<connectivity::Characteristics>(static_cast<std::uint32_t>(l) & static_cast<std::uint32_t>(r));
}

std::ostream& connectivity::operator<<(std::ostream& out, connectivity::Characteristics characteristics)
{
    bool first{true};

    out << "[";

    if ((characteristics & connectivity::Characteristics::connection_goes_via_wifi) != connectivity::Characteristics::none)
    { out << "connection_goes_via_wifi"; first = false; }
    if ((characteristics & connectivity::Characteristics::connection_goes_via_wwan) != connectivity::Characteristics::none)
    { out << (first ? "" : ", ") << "connection_goes_via_wwan"; first = false; }
    if ((characteristics & connectivity::Characteristics::connection_is_roaming) != connectivity::Characteristics::none)
    { out << (first ? "" : ", ") << "connection_is_roaming"; first = false; }
    if ((characteristics & connectivity::Characteristics::connection_has_monetary_costs) != connectivity::Characteristics::none)
    { out << (first ? "" : ", ") << "connection_has_monetary_costs"; first = false; }
    if ((characteristics & connectivity::Characteristics::connection_is_bandwith_limited) != connectivity::Characteristics::none)
    { out << (first ? "" : ", ") << "connection_is_bandwidth_limited"; first = false; }
    if ((characteristics & connectivity::Characteristics::connection_is_volume_limited) != connectivity::Characteristics::none)
    { out << (first ? "" : ", ") << "connection_is_volume_limited"; first = false; }

    out << "]";
    return out;
}

namespace
{
struct Runtime
{
    static Runtime& instance()
    {
        static Runtime runtime;
        return runtime;
    }

    Runtime()
        : system_bus{std::make_shared<core::dbus::Bus>(core::dbus::WellKnownBus::system)},
          executor{core::dbus::asio::make_executor(system_bus)}
    {
        system_bus->install_executor(executor);

        worker_thread = std::move(std::thread
        {
            [this]()
            {
                while(true) {
                    try
                    {
                        system_bus->run();
                        break;  // run exited normally
                    }
                    catch (const std::exception& e)
                    {
                        LOG(WARNING) << e.what();
                    }
                    catch(...)
                    {
                        LOG(WARNING) << "Unexpected exception was raised by the io executor.";
                    }
                }
            }
        });
    }

    ~Runtime()
    {
        system_bus->stop();

        if (worker_thread.joinable())
            worker_thread.join();
    }

    core::dbus::Bus::Ptr system_bus;
    core::dbus::Executor::Ptr executor;
    std::thread worker_thread;
};
}

void connectivity::platform_default_manager(const std::function<void(const std::shared_ptr<Manager>&)>& cb)
{

    auto p = platform_default_manager();
    cb(p);

/*
    w11t::Manager::create([cb](const ::location::Result<w11t::Manager::Ptr>& result)
    {
        if (result)
            cb(result.value());
    });
*/
}

const std::shared_ptr<connectivity::Manager>& connectivity::platform_default_manager()
{
        VLOG(1) << "platform_default_manager";
    printf("platform_default_manager \n");
    try
    {
        static const std::shared_ptr<connectivity::Manager> instance
        {
            new connectivity::OfonoNmConnectivityManager
            {
                Runtime::instance().system_bus
            }
        };

            VLOG(1) << "OfonoNmConnectivityManager";
    printf("OfonoNmConnectivityManager \n");

        return instance;
    }
    catch(...)
    {
    }

    static const std::shared_ptr<connectivity::Manager> dummy_instance
    {
        new dummy::ConnectivityManager{}
    };

    VLOG(1) << "dummy";
    printf("dummy \n");

    return dummy_instance;
}
