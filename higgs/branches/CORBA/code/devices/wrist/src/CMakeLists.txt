# @author Francisco Jesús Arjonilla
# Last Change: Thu Feb 17 06:00 PM 2011 C
set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)

SET(IDL_DIR ../../../idl)
INCLUDE(../../../lib/IDL_command.cmake)

MacroGenerateIDL(CosNaming wrist)

add_library (wrist Exception.cc SerialLinkRS232.cc powercube_telegram.cc wrist.cc wristC.cpp CosNamingC.cpp)

add_executable (WristTestInit WristTestInit.cc wristS.cpp)
target_link_libraries (WristTestInit wrist ${CORBA_LIBS} pthread)

add_executable (wrist_client wrist_client.cc)
target_link_libraries (wrist_client wrist ${CORBA_LIBS})

add_executable (wrist_client_mouse_grab wrist_client_mouse_grab.cc)
target_link_libraries (wrist_client_mouse_grab wrist ${CORBA_LIBS} X11)

add_executable (wrist_server wrist_server.cc wristS.cpp)
target_link_libraries (wrist_server wrist ${CORBA_LIBS} pthread)
install_targets(/bin wrist_server)

