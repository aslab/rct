#!/bin/bash
#./client -ORBInitRef NameService=corbaloc::192.168.2.4:9876/NameService 2>&1 1> /dev/null &
./camera_client -ORBInitRef NameService=corbaloc::higgs:9876/NameService


