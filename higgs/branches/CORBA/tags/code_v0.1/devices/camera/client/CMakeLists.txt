cmake_minimum_required(VERSION 2.6)
project(camera_client)

set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)

SET(IDL_DIR ../../../idl)
INCLUDE(../../../lib/IDL_command.cmake)

MacroGenerateIDL(CosNaming Camera)

add_executable (camera_client camera_client.cc CameraC.cpp CosNamingC.cpp)
target_link_libraries (camera_client ${CORBA_LIBS} dc1394)

