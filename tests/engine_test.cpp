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

#include <location/engine.h>
#include <location/provider.h>
#include <location/provider_selection_policy.h>

#include "mock_provider.h"
#include "null_provider_selection_policy.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
struct MockBus : public location::Bus
{
    /// @brief subscribe makes receiver known to the bus.
    MOCK_METHOD1(subscribe, void(const location::Event::Receiver::Ptr&));

    /// @brief unsubscribe removes receiver from the bus.
    MOCK_METHOD1(unsubscribe, void(const location::Event::Receiver::Ptr&));

    /// @brief dispatch takes event and hands it to all subscribed receivers.
    MOCK_METHOD1(dispatch, void(const location::Event::Ptr& event));
};

struct MockSettings : public location::Settings
{
    // Syncs the current settings to implementation-specific backends.
    MOCK_METHOD0(sync, void());
    // Returns true iff a value is known for the given key.
    MOCK_CONST_METHOD1(has_value_for_key, bool(const std::string&));
    // Gets an integer value known for the given key, or throws Error::NoValueForKey.
    MOCK_METHOD1(get_string_for_key_or_throw, std::string(const std::string&));
    // Sets values known for the given key.
    MOCK_METHOD2(set_string_for_key, bool(const std::string&, const std::string&));
};

location::Bus::Ptr mock_bus()
{
    return std::make_shared<testing::NiceMock<MockBus>>();
}

location::Settings::Ptr mock_settings()
{
    return std::make_shared<::testing::NiceMock<MockSettings>>();
}
}

TEST(Engine, adding_a_null_provider_throws)
{
    location::Engine engine {std::make_shared<NullProviderSelectionPolicy>(), mock_bus(), mock_settings()};

    EXPECT_ANY_THROW(engine.add_provider(location::Provider::Ptr {}););
}

namespace
{
struct MockProviderSelectionPolicy : public location::ProviderSelectionPolicy
{
    ~MockProviderSelectionPolicy() noexcept
    {
    }

    MOCK_METHOD2(determine_provider_selection_for_criteria,
                 location::ProviderSelection(
                     const location::Criteria&,
                     const location::ProviderEnumerator&));
};
}

TEST(Engine, provider_selection_policy_is_invoked_when_matching_providers_to_criteria)
{
    using namespace ::testing;

    MockProviderSelectionPolicy policy;
    location::Engine engine
    {
        location::ProviderSelectionPolicy::Ptr
        {
            &policy,
            [](location::ProviderSelectionPolicy*) {}
        },
        mock_bus(),
        mock_settings()
    };

    EXPECT_CALL(policy, determine_provider_selection_for_criteria(_,_))
            .Times(1)
            .WillOnce(Return(location::ProviderSelection {
                        location::Provider::Ptr{},
                        location::Provider::Ptr{},
                        location::Provider::Ptr{}}));

    auto selection = engine.determine_provider_selection_for_criteria(location::Criteria {});
}

/* TODO(tvoss): We have to disable these tests as the MP is being refactored to not break ABI.
 * We have to enable these tests once we enable the ABI-breaking interface adjustments again.
TEST(Engine, switching_the_engine_off_results_in_providers_being_disabled_and_updates_being_stopped)
{
    using namespace ::testing;

    auto provider = std::make_shared<NiceMock<MockProvider>>();
    provider->state_controller()->start_position_updates();
    provider->state_controller()->start_heading_updates();
    provider->state_controller()->start_velocity_updates();

    auto selection_policy = std::make_shared<NiceMock<MockProviderSelectionPolicy>>();
    location::Engine engine{selection_policy, mock_settings()};
    engine.add_provider(provider);

    EXPECT_CALL(*provider, disable()).Times(1);
    EXPECT_CALL(*provider, stop_position_updates()).Times(1);
    EXPECT_CALL(*provider, stop_velocity_updates()).Times(1);
    EXPECT_CALL(*provider, stop_heading_updates()).Times(1);

    engine.configuration.engine_state = location::Engine::Status::off;
}

TEST(Engine, switching_the_engine_on_after_off_results_in_providers_being_enabled)
{
    using namespace ::testing;

    auto provider = std::make_shared<NiceMock<MockProvider>>();

    auto selection_policy = std::make_shared<NiceMock<MockProviderSelectionPolicy>>();
    location::Engine engine{selection_policy, mock_settings()};
    engine.add_provider(provider);

    EXPECT_CALL(*provider, disable()).Times(1);
    EXPECT_CALL(*provider, enable()).Times(1);

    engine.configuration.engine_state = location::Engine::Status::off;
    engine.configuration.engine_state = location::Engine::Status::on;
}

TEST(Engine, switching_satellite_based_positioning_off_disables_providers_requiring_satellites)
{
    using namespace ::testing;

    auto gps_provider = std::make_shared<NiceMock<MockProvider>>();
    auto network_provider = std::make_shared<NiceMock<MockProvider>>();

    ON_CALL(*gps_provider, requires(Ne(location::Provider::Requirements::satellites)))
            .WillByDefault(Return(true));
    ON_CALL(*gps_provider, requires(location::Provider::Requirements::satellites))
            .WillByDefault(Return(true));
    ON_CALL(*network_provider, requires(location::Provider::Requirements::satellites))
            .WillByDefault(Return(false));

    auto selection_policy = std::make_shared<NiceMock<MockProviderSelectionPolicy>>();
    location::Engine engine{selection_policy, mock_settings()};
    engine.add_provider(gps_provider);
    engine.add_provider(network_provider);

    // Only the mocked gps provider requiring satellites will be disabled.
    EXPECT_CALL(*gps_provider, disable()).Times(1);
    // The network based provider will not be disabled.
    EXPECT_CALL(*network_provider, disable()).Times(0);

    engine.configuration.satellite_based_positioning_state = location::SatelliteBasedPositioningState::off;
}

TEST(Engine, switching_satellite_based_positioning_on_after_off_disables_and_enables_providers_requiring_satellites)
{
    using namespace ::testing;

    auto gps_provider = std::make_shared<NiceMock<MockProvider>>();
    auto network_provider = std::make_shared<NiceMock<MockProvider>>();

    ON_CALL(*gps_provider, requires(Ne(location::Provider::Requirements::satellites)))
            .WillByDefault(Return(true));
    ON_CALL(*gps_provider, requires(location::Provider::Requirements::satellites))
            .WillByDefault(Return(true));
    ON_CALL(*network_provider, requires(location::Provider::Requirements::satellites))
            .WillByDefault(Return(false));

    auto selection_policy = std::make_shared<NiceMock<MockProviderSelectionPolicy>>();
    location::Engine engine{selection_policy, mock_settings()};
    engine.add_provider(gps_provider);
    engine.add_provider(network_provider);

    // Only the mocked gps provider requiring satellites will be disabled.
    EXPECT_CALL(*gps_provider, disable()).Times(1);
    // Only the mocked gps provider requiring satellites will be disabled.
    EXPECT_CALL(*gps_provider, enable()).Times(1);
    // The network based provider will not be disabled.
    EXPECT_CALL(*network_provider, disable()).Times(0);
    // The network based provider will not be disabled.
    EXPECT_CALL(*network_provider, enable()).Times(0);

    engine.configuration.satellite_based_positioning_state = location::SatelliteBasedPositioningState::off;
    engine.configuration.satellite_based_positioning_state = location::SatelliteBasedPositioningState::on;
}
*/
TEST(Engine, reads_state_from_settings_on_construction)
{
    using namespace ::testing;

    std::stringstream ss_engine_state;
    ss_engine_state << location::Engine::Configuration::Defaults::engine_state;
    std::stringstream ss_satellite_based_positioning_state;
    ss_satellite_based_positioning_state << location::Engine::Configuration::Defaults::satellite_based_positioning_state;
    std::stringstream ss_wifi_and_cell_id_reporting_state;
    ss_wifi_and_cell_id_reporting_state << location::Engine::Configuration::Defaults::wifi_and_cell_id_reporting_state;

    auto settings = std::make_shared<NiceMock<MockSettings>>();
    auto selection_policy = std::make_shared<NiceMock<MockProviderSelectionPolicy>>();

    EXPECT_CALL(*settings, has_value_for_key(_))
            .Times(2)
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*settings, get_string_for_key_or_throw(
                    location::Engine::Configuration::Keys::wifi_and_cell_id_reporting_state))
            .Times(1)
            .WillRepeatedly(Return(ss_wifi_and_cell_id_reporting_state.str()));
    EXPECT_CALL(*settings, get_string_for_key_or_throw(
                    location::Engine::Configuration::Keys::engine_state))
            .Times(1)
            .WillRepeatedly(Return(ss_engine_state.str()));

    location::Engine engine{selection_policy, mock_bus(), settings};
}

TEST(Engine, stores_state_from_settings_on_destruction)
{
    using namespace ::testing;

    auto settings = std::make_shared<NiceMock<MockSettings>>();
    auto selection_policy = std::make_shared<NiceMock<MockProviderSelectionPolicy>>();

    EXPECT_CALL(*settings, set_string_for_key(
                    location::Engine::Configuration::Keys::wifi_and_cell_id_reporting_state,
                    _))
            .Times(1)
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*settings, set_string_for_key(
                    location::Engine::Configuration::Keys::engine_state,
                    _))
            .Times(1)
            .WillRepeatedly(Return(true));

    {location::Engine engine{selection_policy, mock_bus(), settings};}
}

