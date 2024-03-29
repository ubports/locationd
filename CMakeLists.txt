cmake_minimum_required(VERSION 2.8)

project(locationd)

if (DEFINED SNAPPY_UBUNTU_CORE)
  add_definitions(-DSNAPPY_UBUNTU_CORE)
endif()

set(LOCATIOND_VERSION_MAJOR 0)
set(LOCATIOND_VERSION_MINOR 0)
set(LOCATIOND_VERSION_PATCH 1)

message(STATUS "${CMAKE_PROJECT_NAME} ${LOCATIOND_VERSION_MAJOR}.${LOCATIOND_VERSION_MINOR}.${LOCATIOND_VERSION_PATCH}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14 -Wall -fno-strict-aliasing -fvisibility=hidden -fvisibility-inlines-hidden -pedantic -Wextra -fPIC -pthread")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CTest)

include(GNUInstallDirs)

find_package(PkgConfig)
find_package(Boost REQUIRED COMPONENTS filesystem locale system program_options)
find_package(GLog)
find_package(GFlags)
find_package(Threads)
pkg_check_modules(DBUS dbus-1 REQUIRED)
pkg_check_modules(DBUS_CPP dbus-cpp REQUIRED)
pkg_check_modules(JSON_C json-c REQUIRED)
pkg_check_modules(LIBAPPARMOR libapparmor REQUIRED)
pkg_check_modules(NET_CPP net-cpp REQUIRED)
pkg_check_modules(PROCESS_CPP process-cpp REQUIRED)
pkg_check_modules(PROPERTIES_CPP properties-cpp REQUIRED)
pkg_check_modules(TRUST_STORE trust-store REQUIRED)
pkg_check_modules(UBUNTU_PLATFORM_HARDWARE_API ubuntu-platform-hardware-api)
pkg_check_modules(GIO gio-2.0)
pkg_check_modules(GIO_UNIX gio-unix-2.0)

option (DISABLE_ERROR_ON_LOCAL_TYPEDEFS_WARNINGS "Disable errors when local typedefs are unused" ON)
if (DISABLE_ERROR_ON_LOCAL_TYPEDEFS_WARNINGS)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-local-typedefs")
endif (DISABLE_ERROR_ON_LOCAL_TYPEDEFS_WARNINGS)

#
# Code style fixer. We rely on clang-format to adjust the formatting of source code.
#
find_program(CLANG_FORMAT_COMMAND NAMES clang-format-3.6 clang-format-3.5)
if (NOT CLANG_FORMAT_COMMAND)
  message(WARNING "Cannot find clang-format >= clang-format-3.5: formatcode target will not be available")
endif()

if (CLANG_FORMAT_COMMAND)
  file(GLOB_RECURSE LOCATIOND_INTERFACE_HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h)
  file(GLOB_RECURSE LOCATIOND_IMPLEMENTATION_FILES ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.cpp)
  add_custom_target(formatcode ${CLANG_FORMAT_COMMAND} -i ${LOCATIOND_INTERFACE_HEADER_FILES} ${LOCATIOND_IMPLEMENTATION_FILES} SOURCES _clang-format)
endif()

include_directories(
  3rd-party/
  3rd-party/ichnaea/include

  ${Boost_INCLUDE_DIRS}
  ${DBUS_INCLUDE_DIRS}
  ${DBUS_CPP_INCLUDE_DIRS}
  ${JSON_C_INCLUDE_DIRS}
  ${LIBAPPARMOR_INCLUDE_DIRS}
  ${NET_CPP_INCLUDE_DIRS}
  ${PROPERTIES_CPP_INCLUDE_DIRS}
  ${PROCESS_CPP_INCLUDE_DIRS}
  ${TRUST_STORE_INCLUDE_DIRS}
  ${GLog_INCLUDE_DIR}
  ${GFlags_INCLUDE_DIR}
  ${GIO_INCLUDE_DIRS}
  ${GIO_UNIX_INCLUDE_DIRS}

  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

file(GLOB_RECURSE LOCATIOND_PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} *.h)

add_subdirectory(3rd-party/ichnaea)

add_subdirectory(data)
add_subdirectory(doc)
add_subdirectory(examples)
add_subdirectory(include)
add_subdirectory(po)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(qt)

# uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
               IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}"
                  -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
