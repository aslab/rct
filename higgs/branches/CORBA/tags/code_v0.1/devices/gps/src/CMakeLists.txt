# @author Francisco Jesús Arjonilla
# Last Change: Thu Feb 17 06:00 PM 2011 C
set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)

set(CMAKE_CXX_FLAGS "-Wall -fPIC")
set(CMAKE_BUILD_TYPE Debug)


SET(IDL_DIR ../../../idl)
INCLUDE(../../../lib/IDL_command.cmake)

MacroGenerateIDL(CosNaming gps)
set(CORBA_SOURCES gpsC.cpp gpsS.cpp CosNamingC.cpp)

add_executable (gps_client gps_client.cc gpsC.cpp CosNamingC.cpp)
target_link_libraries (gps_client ${CORBA_LIBS})

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable (gps_server gps_server.cc gps.cc SerialLinkRS232.cc ${CORBA_SOURCES})
target_link_libraries (gps_server ${CORBA_LIBS} pthread)

install_programs(/../../../../../../../etc/higgs/servants gps_server.sh)
install_targets(/bin gps_server)

