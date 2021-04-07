install(
  DIRECTORY standalone
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/examples)

add_executable(
  connectivity-demo

  standalone/connectivity/connectivity.cpp)

target_link_libraries(
  connectivity-demo

  locationd-connectivity

  ${CMAKE_THREAD_LIBS_INIT}

  ${DBUS_CPP_LDFLAGS}
  ${GLog_LIBRARY}
  ${PROCESS_CPP_LDFLAGS})
