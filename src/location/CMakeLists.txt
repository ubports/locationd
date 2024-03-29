if (UBUNTU_PLATFORM_HARDWARE_API_FOUND)
  add_definitions(-DLOCATION_HAVE_UBUNTU_PLATFORM_HARDWARE_API)
endif()

add_subdirectory(providers)

configure_file(
  config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY
)

include_directories(
  ${CMAKE_BINARY_DIR}/src
  ${CMAKE_BINARY_DIR}/data
  ${UBUNTU_PLATFORM_HARDWARE_API_INCLUDE_DIRS})

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/data/location/dbus")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/connectivity")

find_program(GDBUS_CODEGEN_EXECUTABLE NAMES gdbus-codegen)

add_custom_command(
  OUTPUT "${CMAKE_BINARY_DIR}/data/location/dbus/service_gen.h" "${CMAKE_BINARY_DIR}/data/location/dbus/service_gen.c"
  COMMAND ${GDBUS_CODEGEN_EXECUTABLE} --generate-c-code "${CMAKE_BINARY_DIR}/data/location/dbus/service_gen" "${CMAKE_SOURCE_DIR}/data/location/dbus/service.xml")

add_custom_command(
  OUTPUT "${CMAKE_BINARY_DIR}/data/location/dbus/session_gen.h" "${CMAKE_BINARY_DIR}/data/location/dbus/session_gen.c"
  COMMAND ${GDBUS_CODEGEN_EXECUTABLE} --c-generate-object-manager --generate-c-code "${CMAKE_BINARY_DIR}/data/location/dbus/session_gen" "${CMAKE_SOURCE_DIR}/data/location/dbus/session.xml")

add_custom_command(
  OUTPUT "${CMAKE_BINARY_DIR}/data/location/dbus/provider_gen.h" "${CMAKE_BINARY_DIR}/data/location/dbus/provider_gen.c"
  COMMAND ${GDBUS_CODEGEN_EXECUTABLE} --generate-c-code "${CMAKE_BINARY_DIR}/data/location/dbus/provider_gen" "${CMAKE_SOURCE_DIR}/data/location/dbus/provider.xml")

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/connectivity/w11t_gen.h" "${CMAKE_CURRENT_BINARY_DIR}/connectivity/w11t_gen.c"
  COMMAND ${GDBUS_CODEGEN_EXECUTABLE} --generate-c-code "${CMAKE_CURRENT_BINARY_DIR}/connectivity/w11t_gen" "${CMAKE_CURRENT_SOURCE_DIR}/connectivity/w11t.xml")

add_library(
  nmea

  nmea/scanner.cpp
  nmea/sentence.cpp)

add_library(
  locationd SHARED

  ${LOCATIOND_PUBLIC_HEADERS}

  fusion_provider_selection_policy.cpp
  non_selecting_provider_selection_policy.cpp

  criteria.cpp
  engine.cpp
  event.cpp
  features.cpp
  position.cpp
  provider.cpp
  provider_registry.cpp
  satellite_based_positioning_state.cpp
  settings.cpp
  space_vehicle.cpp
  time_based_update_policy.cpp
  set_name_for_thread.cpp
  system_configuration.cpp
  time_since_boot.cpp
  wifi_and_cell_reporting_state.cpp

  boost_ptree_settings.cpp

  daemon.h
  daemon.cpp
  service.cpp
  result.h
  permission_manager.h
  runtime.h
  runtime.cpp
  runtime_tests.h
  runtime_tests.cpp
  serializing_bus.h
  serializing_bus.cpp
  service_with_engine.h
  service_with_engine.cpp
  session_with_provider.h
  session_with_provider.cpp

  cmds/list.h
  cmds/list.cpp
  cmds/monitor.h
  cmds/monitor.cpp
  cmds/provider.h
  cmds/provider.cpp
  cmds/run.h
  cmds/run.cpp
  cmds/set.h
  cmds/set.cpp
  cmds/status.h
  cmds/status.cpp
  cmds/test.h
  cmds/test.cpp

  util/benchmark.h
  util/benchmark.cpp
  util/cli.h
  util/cli.cpp
  util/do_not_copy_or_move.h
  util/settings.h
  util/settings.cpp

  "${CMAKE_BINARY_DIR}/data/location/dbus/service_gen.h"
  "${CMAKE_BINARY_DIR}/data/location/dbus/service_gen.c"

  "${CMAKE_BINARY_DIR}/data/location/dbus/session_gen.h"
  "${CMAKE_BINARY_DIR}/data/location/dbus/session_gen.c"

  dbus/bus.h
  dbus/bus.cpp
  dbus/codec.h
  dbus/codec.cpp
  dbus/util.h

  dbus/skeleton/service.h
  dbus/skeleton/service.cpp
  dbus/skeleton/session.h
  dbus/skeleton/session.cpp

  dbus/stub/service.h
  dbus/stub/service.cpp
  dbus/stub/session.h
  dbus/stub/session.cpp

  events/all.h
  events/registry.h
  events/registry.cpp
  events/reference_position_updated.cpp
  events/wifi_and_cell_id_reporting_state_changed.cpp

  glib/context.cpp
  glib/holder.h
  glib/runtime.h
  glib/runtime.cpp
  glib/serializing_bus.h
  glib/serializing_bus.cpp
  glib/shared_object.h
  glib/util.h
  glib/util.cpp

  providers/config.cpp

  providers/fusion/provider.h
  providers/fusion/provider.cpp
  providers/proxy.h
  providers/proxy.cpp
  providers/state_tracking_provider.h
  providers/state_tracking_provider.cpp

  "${CMAKE_BINARY_DIR}/data/location/dbus/provider_gen.h"
  "${CMAKE_BINARY_DIR}/data/location/dbus/provider_gen.c"
  providers/remote/provider.h
  providers/remote/provider.cpp
)

add_library(
  locationd-connectivity SHARED

  set_name_for_thread.cpp

  glib/util.h
  glib/util.cpp

  connectivity/cached_radio_cell.cpp
  connectivity/cached_wireless_network.cpp

  connectivity/manager.cpp
  connectivity/radio_cell.cpp
  connectivity/wireless_network.cpp

  connectivity/ofono_nm_connectivity_manager.cpp
  connectivity/w11t_manager.h
  connectivity/w11t_manager.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/connectivity/w11t_gen.h"
  "${CMAKE_CURRENT_BINARY_DIR}/connectivity/w11t_gen.c"
)

set(symbol_map "${CMAKE_SOURCE_DIR}/symbols.map")

set_target_properties(
  locationd

  PROPERTIES
  LINK_FLAGS "${ldflags} -Wl,--version-script,${symbol_map}"
  LINK_DEPENDS ${symbol_map}
  VERSION ${LOCATIOND_VERSION_MAJOR}.${LOCATIOND_VERSION_MINOR}.${LOCATIOND_VERSION_PATCH}
  SOVERSION ${LOCATIOND_VERSION_MAJOR}
)

set_target_properties(
  locationd-connectivity

  PROPERTIES
  LINK_FLAGS "${ldflags} -Wl,--version-script,${symbol_map}"
  LINK_DEPENDS ${symbol_map}
  VERSION ${LOCATIOND_VERSION_MAJOR}.${LOCATIOND_VERSION_MINOR}.${LOCATIOND_VERSION_PATCH}
  SOVERSION ${LOCATIOND_VERSION_MAJOR}
)

add_definitions(${ENABLED_PROVIDER_TARGETS_DEFINITIONS})

target_link_libraries(
  locationd-connectivity

  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  ${DBUS_LIBRARIES}
  ${DBUS_CPP_LDFLAGS}
  ${PROCESS_CPP_LDFLAGS}
  ${GLog_LIBRARY}
  ${GFlags_LIBRARY}
  ${GIO_LDFLAGS}
)

target_link_libraries(
  locationd

  locationd-connectivity

  ${ENABLED_PROVIDER_TARGETS}

  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  ${DBUS_LIBRARIES}
  ${DBUS_CPP_LDFLAGS}
  ${JSON_C_LDFLAGS}
  ${LIBAPPARMOR_LDFLAGS}
  ${NET_CPP_LDFLAGS}
  ${TRUST_STORE_LDFLAGS}
  ${UBUNTU_PLATFORM_HARDWARE_API_LDFLAGS}
  ${GLog_LIBRARY}
  ${GFlags_LIBRARY}
  ${GIO_LDFLAGS}
)

install(
  TARGETS locationd
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
  TARGETS locationd-connectivity
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_executable(
  locationd-bin

  daemon_main.cpp
)

target_link_libraries(
  locationd-bin

  locationd

  ${ENABLED_PROVIDER_TARGETS}
)

set_target_properties(
  locationd-bin
  PROPERTIES OUTPUT_NAME locationd
)

install(
  TARGETS locationd-bin
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
