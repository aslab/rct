#!/bin/bash
#sudo chmod 777 /dev/ttyS0
#sudo service iptables stop
#./laser_server -ORBInitRef NameService=corbaloc::higgs:9876/NameService
laser_server -ORBInitRef NameService=corbaloc::higgs:9876/NameService -ORBListenEndpoints iiop://138.100.76.246
