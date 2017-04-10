PROJECT_NAME=sampleSerial
CC = g++
CFLAGS = -Wall -03 -Isrc
LDFLAGS=

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
