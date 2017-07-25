#!/bin/sh

export PATH=/usr/java/default/bin:${PATH}

java -jar /usr/local/bin/batteries.jar -ORBInitRef NameService=corbaloc::higgs:9876/NameService
