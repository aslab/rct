JAVA_JRE_DIR=/opt/jdk1.6.0_26

SOURCES=arduinoProcessing.java  Command.java  mainClass.java orden.java
LIBS=../lib/core.jar:../lib/RXTXcomm.jar:../lib/serial.jar:.

IDL_SOURCES=../../../idl
IDL_COMPILER=$(JAVA_JRE_DIR)/bin/idlj -fall

all: servant

idl_%: $(IDL_SOURCES)/%.idl
	$(IDL_COMPILER) $<

servant: idl_Arduino idl_CosNaming $(SOURCES)
	$(JAVA_JRE_DIR)/bin/javac -cp $(LIBS) $(SOURCES)
	$(JAVA_JRE_DIR)/bin/jar cfe arduino.jar mainClass *.class ../lib/*.jar higgs/*.class

run:
	./arduino.sh

clean:
	rm -rf higgs CosNaming *class *jar

install_libs:
	cp ../lib/*.jar $(JAVA_JRE_DIR)/jre/lib/ext
	cp ../lib/*.so /usr/local/lib

install:
	echo "Note: make install_libs before running."
	cp higgs_arduino.conf /etc/init
	cp arduino.jar /usr/local/bin
	echo "BEWARE! Do not forget to add the path to the java libraries and to set LD_LIBRARY_PATH to /usr/local/lib in .profile"

