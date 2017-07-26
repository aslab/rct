cmake_minimum_required(VERSION 2.6)
CMAKE_POLICY(SET CMP0015 NEW)

FIND_PACKAGE( OpenCV REQUIRED )
IF (${OpenCV_VERSION} VERSION_LESS 2.0.0)
MESSAGE(FATAL_ERROR �OpenCV version is not compatible : ${OpenCV_VERSION}�)
ENDIF()

set(CODEC_LIBS avcodec avutil avformat swscale GLU GL glut glui Xv Xext X11)
set(CORBA_LIBS TAO_RTCORBA TAO_RTPortableServer TAO_PortableServer TAO_CosNaming TAO ACE TAO_AnyTypeCode)

if(APPLE) 
set(CMAKE_CXX_FLAGS "-Wall -D_XOPEN_SOURCE -D__STDC_CONSTANT_MACROS -DNOTEXTURE2D -I/opt/ACE-5.7.2/include -I/opt/TAO-1.7.2/include -L/opt/ACE-5.7.2/i386/lib -L/opt/TAO-1.7.2/i386/lib -I/usr/X11/include -L/usr/X11/lib -I/opt/local/include -L/opt/local/lib -framework Carbon")
set(CMAKE_C_FLAGS "-Wall -D_XOPEN_SOURCE -DNOTEXTURE2D -I/usr/X11/include -I/opt/local/include")
endif(APPLE)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux") 
set(CMAKE_CXX_FLAGS "-Wall -D_XOPEN_SOURCE -D__STDC_CONSTANT_MACROS -DNOTEXTURE2D -I/opt/ACE-5.7.2/include -I/opt/TAO-1.7.2/include -L/opt/ACE-5.7.2/i386/lib -L/opt/TAO-1.7.2/i386/lib -I/usr/X11/include -L/usr/X11/lib -I/opt/local/include -L/opt/local/lib")
set(CMAKE_C_FLAGS "-Wall -D_XOPEN_SOURCE -DNOTEXTURE2D ")
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux") 

set(CMAKE_BUILD_TYPE Debug)
INCLUDE(../../lib/IDL_command.cmake)

MacroGenerateIDL(CosNaming Camera)

add_executable(camera server.cpp CameraC.cpp CameraS.cpp)
if(APPLE) 
target_link_libraries(camera ${CORBA_LIBS} dc1394 IL ILU IOKit pthread ${OpenCV_LIBS})
endif(APPLE)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux") 
target_link_libraries(camera ${CORBA_LIBS} dc1394 IL ILU pthread ${OpenCV_LIBS})
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

install_programs(/../../../../../../../etc/higgs/servants camera.sh)
install_targets(/bin camera)

#add_executable(sdl server-sdl.cpp CameraC.cpp CameraS.cpp)
#target_link_libraries(camera ${CORBA_LIBS} dc1394 SDL)
#install_targets(/bin sdl)

add_executable(camera_client client.cpp CameraC.cpp initGL.c encode.cpp)
if(APPLE) 
target_link_libraries(camera_client ${CORBA_LIBS} ${CODEC_LIBS} /opt/local/lib/libglui.a dc1394 IL ILU IOKit ${OpenCV_LIBS})
endif(APPLE)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
target_link_libraries(camera_client ${CORBA_LIBS} ${CODEC_LIBS} libglui.a dc1394 IL ILU ${OpenCV_LIBS})
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

