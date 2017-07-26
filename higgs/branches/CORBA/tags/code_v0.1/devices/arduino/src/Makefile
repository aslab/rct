JAVA_JRE_DIR=/usr/java/jdk1.6.0_20

SOURCES=arduinoProcessing.java  Command.java  mainClass.java orden.java
LIBS=../lib/core.jar:../lib/RXTXcomm.jar:../lib/serial.jar:.

IDL_SOURCES=../../../idl
IDL_COMPILER=idlj -fall

all: servant

idl_%: $(IDL_SOURCES)/%.idl
	$(IDL_COMPILER) $<

servant: idl_Arduino idl_CosNaming $(SOURCES)
	javac $(SOURCES) -cp $(LIBS)
	jar cfe arduino.jar mainClass *.class ../lib/*.jar higgs/*.class

run:
	./arduino.sh

clean:
	rm -rf higgs CosNaming *class *jar

install_libs:
	cp ../lib/*.jar $(JAVA_JRE_DIR)/lib/ext
	cp ../lib/*.so /usr/local/lib
	cp arduino.jar /usr/local/bin

install:
	cp arduino.sh /etc/higgs/servants
	cp arduino.jar /usr/local/bin

