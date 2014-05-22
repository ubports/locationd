#include <com/ubuntu/location/connectivity/manager.h>

#include <core/posix/signal.h>

#include <cstdlib>

namespace location = com::ubuntu::location;

namespace
{
// Just convenience to safe some typing.
typedef std::vector<location::connectivity::RadioCell> RadioCells;
typedef std::vector<location::connectivity::WirelessNetwork::Ptr> WirelessNetworks;
}

// This example illustrates the usage of the location-service-specific connectivity API.
// The setup for obtaining measurements of wifis and radio cells is as follows:
//
//   (1.) Obtain an instance of location::connectivity::Manager.
//   (2.) Connect to the changed signals of the wifi and cell properties and react according to your component's requirements.
//   (3.) Bootstrap your own setup by explicitly getting all visible wifis and connected cells.
int main(int argc, char** argv)
{
    // We catch sig-term to exit cleanly.
    auto trap = core::posix::trap_signals_for_all_subsequent_threads({core::posix::Signal::sig_term});
    trap->signal_raised().connect([trap](core::posix::Signal)
                                  {
                                      trap->stop();
                                  });

    // Trying to acquire a default implementation.
    auto cm = location::connectivity::platform_default_manager();

    if (not cm)
    {
        std::cerr << "Could not get hold of a connectivity::Manager implementation, aborting..." << std::endl;
        std::exit(1);
    }

    // We subscribe to changes for visible wireless networks.
    cm->visible_wireless_networks().changed().connect([](const WirelessNetworks& networks)
    {
        std::cout << "Visible wireless networks changed:" << std::endl;

        // Iterate over all visible wireless networks.
        for (const auto& wifi: networks)
        {
            std::cout << wifi->ssid().get() << ", timestamp: ";
            auto ts = std::chrono::system_clock::to_time_t(wifi->timestamp().get());
            std::cout << std::ctime(&ts);

            // We don't want to keep the object alive
            std::weak_ptr<location::connectivity::WirelessNetwork> wp
            {
                wifi
            };

            // Subscribe to cell updates. Please note that this is not considering
            // the case of subscribing to already known wifis. We leave this up
            // to consumers of the api.
            wifi->signal_strength().changed().connect([wp](const location::connectivity::WirelessNetwork::SignalStrength& s)
            {
                auto sp = wp.lock();
                if (sp)
                    std::cout << "Signal strength changed for wifi " << sp->ssid().get() << ": " << s << std::endl;
            });

            std::cout << "  " << *wifi << std::endl;
        }
    });

    // We subscribe to changes for connected radio cells.
    cm->connected_radio_cells().changed().connect([](const RadioCells& cells)
    {
        std::cout << "Connected radio cells changed:" << std::endl;

        for (const auto& cell : cells)
            std::cout << "  " << cell << std::endl;
    });

    // Iterate over all radio cells that the device is connected with.
    for (const auto& cell : cm->connected_radio_cells().get())
        std::cout << cell << std::endl;

    // Iterate over all networks that are visible right now.
    for (const auto& wifi: cm->visible_wireless_networks().get())
    {
        // We don't want to keep the object alive
        std::weak_ptr<location::connectivity::WirelessNetwork> wp{wifi};

        // Subscribe to cell updates
        wifi->signal_strength().changed().connect([wp](const location::connectivity::WirelessNetwork::SignalStrength& s)
        {
            auto sp = wp.lock();
            if (sp)
                std::cout << "Signal strength changed for wifi " << sp->ssid().get() << ": " << s << std::endl;
        });

        std::cout << *wifi << std::endl;
    }
    
    // Request a scan for wireless networks.
    try
    {
        cm->request_scan_for_wireless_networks();
    } catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    trap->run();

    return 0;
}    


