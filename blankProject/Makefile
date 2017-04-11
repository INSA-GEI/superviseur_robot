INPUT_FILE=blankTemplate
SRC_PATH=./src/
HEADER_PATH=./header/

CC = g++
CFLAGS = -Wall -03
LDFLAGS= -L/opt/vc/lib  -I/usr/local/include -lopencv_highgui -lopencv_core   -lopencv_imgcodecs -lraspicam_cv -lopencv_imgproc -lpthread

EXEC=$(INPUT_FILE).elf
SRC_REQUIRED=../obj/imagerie.o ../obj/serial.o ../obj/tcpServer.o
SRC=$(wildcard $(SRC_PATH)*.cpp)
HEADER=$(wildcard $(HEADER_PATH)*.h)
OBJ=$(SRC:.cpp=.o)

all:$(EXEC)

$(EXEC) : $(SRC_REQUIRED) $(OBJ)
	  $(CC) $(INPUT_FILE).cpp -o $@ $^ $(LDFLAGS)

%o	: %.cpp $(HEADER)
	  $(CC) $(CLAGS) -o $@ -c $<

clean:
	rm -f *.o src/*.o

release: all clean
