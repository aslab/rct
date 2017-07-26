JAVA_JRE_DIR=/usr/java/default

SOURCES=baterias.java datos.java mainClass.java promedio.java

IDL_SOURCES=../../../idl
IDL_COMPILER=idlj -fall

all: servant

idl_%: $(IDL_SOURCES)/%.idl
	$(IDL_COMPILER) $<

servant: idl_BatteryModel idl_CosNaming idl_Arduino $(SOURCES)
	javac $(SOURCES)
	jar cfe batteries.jar mainClass *.class higgs/*.class

run:
	./batteries.sh

clean:
	rm -rf higgs CosNaming *class *jar

install:
	cp batteries.sh /etc/higgs/servants
	cp batteries.jar /usr/local/bin

