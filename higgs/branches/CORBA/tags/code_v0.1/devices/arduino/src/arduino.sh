#!/bin/sh

export PATH=/usr/java/default/bin:${PATH}

java -jar /usr/local/bin/arduino.jar -ORBInitRef NameService=corbaloc::higgs:9876/NameService
