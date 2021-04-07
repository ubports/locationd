set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Location REQUIRED)
find_package(Qt5DBus REQUIRED)

qt5_add_resources(POSITION_RESOURCES position.qrc)

set_source_files_properties(
    ${CMAKE_SOURCE_DIR}/data/location/dbus/session.xml
    ${CMAKE_SOURCE_DIR}/data/location/dbus/service.xml
    PROPERTIES INCLUDE dbusdatatypes.h
)

qt5_add_dbus_interface(POSITION_INTERFACES
    ${CMAKE_SOURCE_DIR}/data/location/dbus/service.xml serviceInterface
)

qt5_add_dbus_interface(POSITION_INTERFACES
    ${CMAKE_SOURCE_DIR}/data/location/dbus/session.xml sessionInterface
)

add_library(
  qtposition_locationd SHARED

  qgeopositioninfosource_locationd.cpp
  qgeopositioninfosourcefactory_locationd.cpp

  ${POSITION_RESOURCES}
  ${POSITION_INTERFACES}
)

# Ideally, we would read the plugin installation location from cmake
# but this does not work currently.
set(PLUGIN_INSTALL_LOCATION "${CMAKE_INSTALL_LIBDIR}/qt5/plugins/position")
# get_target_property(PLUGIN_LOCATION Qt5::Location PLUGIN_LOCATION)

message(STATUS "Installing Qt5 location plugin to: ${PLUGIN_INSTALL_LOCATION}")

qt5_use_modules(qtposition_locationd Core Gui Location)
qt5_use_modules(qtposition_locationd Gui Location)

target_link_libraries(
  qtposition_locationd

  ${CMAKE_THREAD_LIBS_INIT}

  Qt5::Core
  Qt5::Gui
  Qt5::Location
  Qt5::DBus
)

install(
  TARGETS qtposition_locationd
  LIBRARY DESTINATION ${PLUGIN_INSTALL_LOCATION})


add_executable(locationd_test_qt
  test.cpp

  ${POSITION_INTERFACES}
)

target_link_libraries(
  locationd_test_qt

  Qt5::Core
  Qt5::DBus
)
