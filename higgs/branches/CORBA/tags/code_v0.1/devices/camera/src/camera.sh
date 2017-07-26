#!/bin/sh
killall camera
dc1394_reset_bus
#camera -ORBInitRef NameService=corbaloc::higgs:9876/NameService -ORBListenEndpoints iiop://138.100.76.246
./camera -ORBInitRef NameService=corbaloc::138.100.76.250:9876/NameService -ORBListenEndpoints iiop://138.100.76.250:9878
