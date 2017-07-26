# CMakeLists for WorldModel
# Substitute names beginning with _ for WorldModel
cmake_minimum_required(VERSION 2.6)
project(WorldModel)

set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)

include_directories(../../control_libraries/src)
link_directories(../../control_libraries/src)

set(CMAKE_CXX_FLAGS "-Wall -fPIC")
set(CMAKE_BUILD_TYPE Debug)

# CORBA related sources.
INCLUDE(../../lib/IDL_command.cmake)

#CORBA related stuff for Higgs
SET(IDL_DIR ../../idl/)
MacroGenerateIDL(CosNaming HiggsTypes laser Arduino gps WorldModel)
 
set(CORBA_SOURCES WorldModelC.cpp WorldModelS.cpp CosNamingC.cpp HiggsTypesC.cpp laserC.cpp gpsC.cpp ArduinoC.cpp)

# Client.
#add_executable (WorldModel_client WorldModel_client.cc ${CORBA_SOURCES})
#target_link_libraries (WorldModel_client ${CORBA_LIBS})

# Servant.
add_executable (WorldModel_server ${CORBA_SOURCES} WorldModel_impl.cpp WorldModel_server.cpp)
target_link_libraries (WorldModel_server ${CORBA_LIBS} control newmat) 

# Installation of servant on onboard computer.
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#install_programs(/../../../../../etc/higgs/servants WorldModel_server.sh)
#install_targets(/bin WorldModel_server)

