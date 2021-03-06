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
#ifndef LOCATION_PROVIDERS_UBX_PROVIDER_H_
#define LOCATION_PROVIDERS_UBX_PROVIDER_H_

#include <location/provider.h>
#include <location/provider_registry.h>
#include <location/runtime.h>
#include <location/nmea/sentence.h>
#include <location/providers/ubx/_8/assist_now_online_client.h>
#include <location/providers/ubx/_8/serial_port_receiver.h>

#include <boost/filesystem.hpp>

#include <iosfwd>
#include <thread>

namespace location
{
namespace providers
{
namespace ubx
{
// ubx::Provider integrates GNSS receivers relying on
// ublox chipsets with locationd.
//
// In this version, only receivers connected to a serial port
// are supported. More to this, this version only reads NMEA sentences
// and does not support the proprietary ublox protocol.
//
// Configuration parameters:
//   - device[=/dev/ttyUSB1] serial device connecting to the receiver.
class Provider : public location::Provider, public std::enable_shared_from_this<Provider>
{
public:
    enum class Protocol
    {
        ubx,  // Rely on ubx.
        nmea  // Rely on nmea.
    };

    // Configuration bundles all construction time parameters.
    struct Configuration
    {
        Protocol protocol;                                  // The protocol used for communicating with the receiver.
        boost::filesystem::path device;                     // Serial device used for communicating with the receiver.
        struct
        {
            bool enable;                                    // Whether or not the provider should use AssistNow.
            std::string token;                              // Token for validating requests to the AssistNow service.
            boost::posix_time::seconds acquisition_timeout; // Query assistance data after this many seconds.
        } assist_now;                                       // All parameters for configuring AssistNow go here.
    };

    static void add_to_registry();

    // Instantiates a new provider instance, populating the configuration object
    // from the provided property bundle. Please see dummy::Configuration::Keys
    // for the list of known options.
    static Provider::Ptr create_instance(const util::settings::Source&);

    // Create a new instance with configuration.
    static std::shared_ptr<Provider> create(const Configuration& configuration);

    // Cleans up all resources and stops the updates.
    ~Provider() noexcept;

    // Resets the chipset and drops all cached data.
    // The next positioning request will be a cold start.
    void reset();

    // From Provider
    void on_new_event(const Event& event) override;

    void enable() override;
    void disable() override;
    void activate() override;
    void deactivate() override;

    Requirements requirements() const override;
    bool satisfies(const Criteria& criteria) override;
    const core::Signal<Update<Position>>& position_updates() const override;
    const core::Signal<Update<units::Degrees>>& heading_updates() const override;
    const core::Signal<Update<units::MetersPerSecond>>& velocity_updates() const override;

private:
    // Relays incoming sentences to a provider instance.
    struct Monitor : public std::enable_shared_from_this<ubx::Provider::Monitor>, public _8::Receiver::Monitor, public boost::static_visitor<>
    {
        // From Receiver::Monitor
        void on_new_ubx_message(const _8::Message& message) override;
        void on_new_nmea_sentence(const nmea::Sentence& sentence) override;

        template<typename T>
        void operator()(const T&) const {}

        void operator()(const _8::nav::Pvt& pvt);

        void operator()(const nmea::Gga& gga);
        void operator()(const nmea::Gsa& gsa);
        void operator()(const nmea::Gll& gll);
        void operator()(const nmea::Gsv& gsv);
        void operator()(const nmea::Rmc& rmc);
        void operator()(const nmea::Txt& txt);
        void operator()(const nmea::Vtg& vtg);

        std::weak_ptr<Provider> provider;
    };

    // Creates a new provider instance talking via device to the ubx chipset.
    Provider(const Configuration& configuration);

    std::shared_ptr<Provider> finalize_construction();

    void configure_gnss();
    void configure_protocol();

    void request_assist_now_online_data(const Optional<Position>& position);

    Configuration configuration;
    std::shared_ptr<location::Runtime> runtime;
    std::shared_ptr<Monitor> monitor;
    std::shared_ptr<_8::SerialPortReceiver> receiver;
    std::shared_ptr<_8::AssistNowOnlineClient> assist_now_online_client;
    boost::asio::deadline_timer acquisition_timer;

    struct
    {
        core::Signal<Update<Position>> position;
        core::Signal<Update<units::Degrees>> heading;
        core::Signal<Update<units::MetersPerSecond>> velocity;
    } updates;
};

std::istream& operator>>(std::istream&, Provider::Protocol&);
std::ostream& operator<<(std::ostream&, Provider::Protocol);

}  // namespace ubx
}  // namespace providers
}  // namespace location

#endif // LOCATION_PROVIDERS_UBX_PROVIDER_H_
