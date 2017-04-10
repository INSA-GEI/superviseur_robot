PROJECT_NAME=sampleVideo
CC = g++
CFLAGS = -Wall -03
LDFLAGS= -L/opt/vc/lib -I/usr/local/include -lraspicam -lmmal -lmmal_core -lmmal_util -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lraspicam_cv -lopencv_imgproc -lpthread

EXEC=$(PROJECT_NAME).elf
SRC=$(wildcard ../src/*.cpp)
LIB=$(wildcard ../src/*.h)
OBJ=$(SRC:.cpp=.o)

all:$(EXEC)

$(EXEC) : $(OBJ) main.o
	  $(CC) -o $@ $^ $(LDFLAGS)

%o	: %.cpp $(LIB)
	  $(CC) $(CLAGS) -o $@ -c $<

clean:
	rm -f *.o src/*.o

release: all clean
