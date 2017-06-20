# @author Francisco Jesús Arjonilla
# Last Change: Thu Feb 17 06:00 PM 2011 C
set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)

set(CMAKE_CXX_FLAGS "-Wall -fPIC")
set(CMAKE_BUILD_TYPE Debug)

SET(IDL_DIR ../../../idl)
INCLUDE(../../../lib/IDL_command.cmake)

MacroGenerateIDL(CosNaming laser)
set(CORBA_SOURCES laserC.cpp laserS.cpp CosNamingC.cpp)

add_executable (laser_client laser_client.cc ${CORBA_SOURCES})
target_link_libraries (laser_client ${CORBA_LIBS})

add_executable (laser_server laser_server.cc ProtLMS.cpp PortCOM.cpp ${CORBA_SOURCES})
target_link_libraries (laser_server ${CORBA_LIBS} pthread)

install_programs(/../../../../../../../etc/higgs/servants laser_server.sh)
install_targets(/bin laser_server)

