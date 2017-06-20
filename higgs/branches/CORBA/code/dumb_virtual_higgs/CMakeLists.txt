# @author Francisco J. Arjonilla
# Last Change: Thu Feb 17 06:00 PM 2011 C
cmake_minimum_required(VERSION 2.6)
project(dumb_virtual_higgs)

set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)

set(CMAKE_CXX_FLAGS "-Wall -fPIC")
set(CMAKE_BUILD_TYPE Debug)

# CORBA related sources.
INCLUDE(../lib/IDL_command.cmake)
SET(IDL_DIR ../idl)
MacroGenerateIDL(CosNaming Arduino gps laser wrist Pioneer2AT)
set(CORBA_SOURCES CosNamingC.cpp
       ArduinoC.cpp ArduinoS.cpp
       gpsC.cpp gpsS.cpp
       laserC.cpp laserS.cpp
       wristC.cpp wristS.cpp
       Pioneer2ATC.cpp Pioneer2ATS.cpp)

# Servant.
add_executable (dumb_virtual_higgs main.cc servants.cc ${CORBA_SOURCES})
target_link_libraries (dumb_virtual_higgs ${CORBA_LIBS} pthread)

