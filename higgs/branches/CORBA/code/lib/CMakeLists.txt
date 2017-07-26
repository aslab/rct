# Example configuration file for CMAKE.
# Substitute names begginning with _
cmake_minimum_required(VERSION 2.6)
project(_module)

set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)
# Remove these two lines if not using ARIA.
include_directories(/usr/local/Aria/include/)
link_directories(/usr/local/Aria/lib/)

set(CMAKE_CXX_FLAGS "-Wall -fPIC")
set(CMAKE_BUILD_TYPE Debug)

# CORBA related sources.
INCLUDE(../../lib/IDL_command.cmake)
MacroGenerateIDL(CosNaming _module)
set(CORBA_SOURCES _moduleC.cpp _moduleS.cpp CosNamingC.cpp)

# Client.
add_executable (_module_client _module_client.cc ${CORBA_SOURCES})
target_link_libraries (_module_client ${CORBA_LIBS})

# Servant.
add_executable (_module_server _module_server.cc ${CORBA_SOURCES})
target_link_libraries (_module_server ${CORBA_LIBS} Aria pthread dl)

# Installation of servant on onboard computer.
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
install_programs(/../../../../../../../etc/higgs/servants _module_server.sh)
install_targets(/bin _module_server)

