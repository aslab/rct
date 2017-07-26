#!/bin/sh
gps_server -ORBInitRef NameService=corbaloc::higgs:9876/NameService -ORBListenEndpoints iiop://138.100.76.246
