//
// Created by lucien on 05/04/17.
//

#ifndef DUMBERC_SERIAL_H_H
#define DUMBERC_SERIAL_H_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>


#define PING 'p'
#define BACKIDLE 'r'
#define WITH_WD  'W'
#define RELOAD 'w'
#define GETVBAT 'v'
#define GETBUSY 'b'
#define WITHOUT_WD 'u'
#define SETMOVE 'M'
#define SETTURN 'T'
#define GOFORWARD 'F'
#define GOBACK 'B'
#define TURNLEFT 'L'
#define TURNRIGHT 'R'
#define STOPMOVE 'S'

#define ROBOT_TIMED_OUT -3
#define ROBOT_UKNOW_CMD -2
#define ROBOT_ERROR -1
#define ROBOT_CHEKSUM -4

#define serialPort "/dev/ttyS0"

int robotOpenCom(const char * path=serialPort);
int readRobot(void);
int robotCloseCom(void);
int robotCmd(char cmd, char * arg=NULL);
int sendCmd(char cmd, char * arg=NULL);

#endif //DUMBERC_SERIAL_H_H
