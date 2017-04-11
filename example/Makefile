LDFLAGS= -L/opt/vc/lib  -I/usr/local/include -lopencv_highgui -lopencv_core   -lopencv_imgcodecs -lraspicam_cv -lopencv_imgproc -lpthread

all :
	make serial
	make video
	make ui

serial :
	g++ serialExample.cpp -o serialExample.elf  ../obj/serial.o
video :
	g++ videoExample.cpp -o videoExample.elf ../obj/serial.o ../obj/imagerie.o ../obj/tcpServer.o $(LDFLAGS)

ui :
	g++ uiExample.cpp -o uiExample.elf ../obj/serial.o ../obj/imagerie.o ../obj/tcpServer.o $(LDFLAGS)

clean : 
	rm *.elf
