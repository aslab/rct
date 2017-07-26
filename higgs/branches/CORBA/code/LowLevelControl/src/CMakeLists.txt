# Example configuration file for CMAKE.
# Substitute names begginning with _
cmake_minimum_required(VERSION 2.6)
project(LowLevelControl)

set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)
# Remove these two lines if not using ARIA.
include_directories(../../control_libraries/src; /usr/include/)
link_directories(../../control_libraries/src; /usr/lib/)

set(CMAKE_CXX_FLAGS "-Wall -fPIC")
set(CMAKE_BUILD_TYPE Debug)

# CORBA related sources.
INCLUDE(../../lib/IDL_command.cmake)

#CORBA related stuff for Higgs
SET(IDL_DIR ../../idl/)
MacroGenerateIDL( CosNaming Pioneer2AT laser gps Arduino WorldModel LowLevelControl)

set(CORBA_SOURCES LowLevelControlC.cpp LowLevelControlS.cpp CosNamingC.cpp)

# Client.
#add_executable (LowLevelControl_client LowLevelControl_client.cpp ${CORBA_SOURCES})
#target_link_libraries (LowLevelControl_client ${CORBA_LIBS})

# Servant.
add_executable (LowLevelControl_server ${CORBA_SOURCES} ArduinoC.cpp gpsC.cpp laserC.cpp Pioneer2ATC.cpp WorldModelC.cpp StateModel_wrapper.cpp LowLevelControl_impl.cpp LowLevelControl_server.cpp)
target_link_libraries (LowLevelControl_server ${CORBA_LIBS} newmat cv control )

# Installation of servant on onboard computer.
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#install_programs(/../../../../../etc/higgs/servants LowLevelControl_server.sh)
#install_targets(/bin LowLevelControl_server)

