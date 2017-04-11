#include "../src/imagerie.h"
#include "../src/serial.h"
#include "../src/tcpServer.h" // include himself imagerie.h
#include <pthread.h>
#include "header/monSuperProg.h"

using namespace std;
using namespace cv;
using namespace raspicam;


int main() {
    helloWorld();
    return 0;
}
