# @author Francisco Jesús Arjonilla
# Last Change: Thu Feb 17 06:00 PM 2011 C
cmake_minimum_required(VERSION 2.6)
project(arduino_client)

set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)

SET(IDL_DIR ../../../idl)
INCLUDE(../../../lib/IDL_command.cmake)

MacroGenerateIDL(CosNaming Arduino)

add_executable (arduino_client arduino_client.cc ArduinoC.cpp CosNamingC.cpp)
target_link_libraries (arduino_client ${CORBA_LIBS})

#add_executable (wrist_client_mouse_grab wrist_client_mouse_grab.cc)
#target_link_libraries (wrist_client_mouse_grab wrist ${CORBA_LIBS} X11)

