# Copyright © 2017 Canonical Ltd.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Thomas Voss <thomas.voss@canonical.com>

configure_file(
  locationd.pc.in locationd.pc @ONLY
)

configure_file(
  locationd-connectivity.pc.in locationd-connectivity.pc @ONLY
)

configure_file(
  locationd.conf.in locationd.conf @ONLY
)

configure_file(
  locationd-trust-stored.conf.in locationd-trust-stored.conf @ONLY
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/locationd.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/locationd-connectivity.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/com.ubuntu.location.Service.conf
  DESTINATION /etc/dbus-1/system.d/
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/locationd.conf
  DESTINATION /etc/init/
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/locationd-trust-stored.conf
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/upstart/sessions/
)

install(
  FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/location/dbus/provider.xml
  ${CMAKE_CURRENT_SOURCE_DIR}/location/dbus/service.xml
  ${CMAKE_CURRENT_SOURCE_DIR}/location/dbus/session.xml
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/locationd/dbus/
)
