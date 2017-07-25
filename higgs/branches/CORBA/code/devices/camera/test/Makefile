 

ACE_ROOT = /usr/src/debug/ACE_wrappers

executables = client testxv
generated = Laser?.*

minimal:  client testxv dc1394_multiview dc1394_multiview2 dc1394_multiview3

client: client.cpp
	g++ -g -o client -L/usr/X11R6/lib -lXv -lX11 -lstdc++ client.cpp

dc1394_multiview: dc1394_multiview.c
	gcc -g -o dc1394_multiview -I/sw/include -L/usr/X11R6/lib -L/sw/lib -ldc1394 -lXv -lXext -lX11 dc1394_multiview.c

dc1394_multiview2: dc1394_multiview2.c
	gcc -g -o dc1394_multiview2 -I/sw/include -L/usr/X11R6/lib -L/sw/lib -ldc1394 -lXv -lXext -lX11 dc1394_multiview2.c

dc1394_multiview3: dc1394_multiview3.c
	gcc -g -o dc1394_multiview3 -I/usr/X11R6/include -I/sw/include -L/usr/X11R6/lib -L/sw/lib -ldc1394 -lGLU -lGL -lglut -lXv -lXext -lX11 dc1394_multiview3.c

dc1394_multiview4: dc1394_multiview4.c
	gcc -g -o dc1394_multiview4 -I/usr/X11R6/include -I/sw/include -L/usr/X11R6/lib -L/sw/lib -ldc1394 -lGLU -lGL -lglut -lXv -lXext -lX11 dc1394_multiview4.c

testxv: testxv.c
	gcc -g -o testxv -L/usr/X11R6/lib -lXv -lXext -lX11 testxv.c

server: server.cpp CamaraS.h CamaraS.cpp
	g++ -g -o server -L$(ACE_ROOT)/lib -L /usr/local/Aria/lib -I /opt/gcc34/include/c++/3.4.6/backward/ -D __ACE_INLINE__ -ldc1394 -lACE -lTAO -lTAO_PortableServer -lTAO_CosNaming -lTAO_AnyTypeCode -lstdc++ -I$(ACE_ROOT) -I$(TAO_ROOT) -Wno-deprecated server.cpp

.PHONY: clean
clean:
	-rm $(executables)
	-rm $(generated)
