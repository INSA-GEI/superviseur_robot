#include "serial.h"

int fd;

int robotOpenCom(const char * path)
{
    struct termios options;
    fd = open(path, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd !=-1)
    {
        fcntl(fd, F_SETFL, 0);
        tcgetattr(fd, &options);
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        cfsetospeed (&options, B115200);
        cfsetispeed (&options, B115200);
        options.c_cc[VMIN]=0;
        options.c_cc[VTIME]=0;
        tcsetattr(fd, TCSANOW, &options);
        return 0;
    }
    else
    {
        perror("can't openSerial");
        return -1;
    }
}

int getChar(char * c)
{
    int n =0;
    int delay =0;
    while((n=read(fd,c,1)) <=0)
    {
        usleep(5000);
        delay++;
        if(delay > 10)
        {
            return ROBOT_TIMED_OUT;
        }

    }
    return n;
}

int readSerial(char * msg)
{
    char car;
    int i =0,j=0;
    for(j = 0 ; j < 20 ; j++)
        msg[j]=0;
    while(car !='\r' && car!='\n')
    {
        if(i>=20)
            return -5;

        if(getChar(&car)==ROBOT_TIMED_OUT)
        {
            return ROBOT_TIMED_OUT;
        }
        msg[i] = car;
        i++;
    }
    return i;
}

char checkSumGO(char * msg)
{
    char resultat = 0;
    int i = 0;
    int taille = strlen(msg);
    for(i=0;i<taille;i++)
    {
        resultat^=msg[i];
    }
    return resultat;

}

int sendCmd(char cmd, char * arg)
{
    char cmdWithArg[20]={};
    cmdWithArg[0]=cmd;
    switch(cmd)
    {
        case GOFORWARD: strcpy(cmdWithArg,"M=+64000");
            break;
        case GOBACK:    strcpy(cmdWithArg,"M=-64000");
            break;
        case TURNLEFT:  strcpy(cmdWithArg,"T=+64000");
            break;
        case TURNRIGHT: strcpy(cmdWithArg,"T=-64000");
            break;
        case STOPMOVE:  strcpy(cmdWithArg,"M=0");
            break;
        case SETMOVE:   strcat(cmdWithArg,"=");
            strcat(cmdWithArg,arg);
            break;
        case SETTURN:   strcat(cmdWithArg,"=");
            strcat(cmdWithArg,arg);
            break;
    }
    int sizeCmd = strlen(cmdWithArg);
    cmdWithArg[sizeCmd] = checkSumGO(cmdWithArg);
    cmdWithArg[sizeCmd+1] = '\r';
    cmdWithArg[sizeCmd+2] = '\0';
    return write(fd,cmdWithArg,strlen(cmdWithArg));
}

int readRobot(void)
{
    char msg[20];
    int b;
    if((b = readSerial(msg))!=ROBOT_TIMED_OUT)
    {
        int taille = strlen(msg);
        char checksum = msg[taille-2];
        msg[taille-1] = 0;
        msg[taille-2] = 0;
        if(checksum!=checkSumGO(msg))
        {
            return ROBOT_CHEKSUM;
        }
        else
        {
            switch(msg[0])
            {
                case 'O' : return 0;
                case 'E' : return ROBOT_ERROR;
                case 'C' : return ROBOT_UKNOW_CMD;
                default :  return atoi(&msg[0]);
            }
        }
    }
    else
    {
        return ROBOT_TIMED_OUT;
    }
}

int robotCmd(char cmd, char * arg)
{
    sendCmd(cmd,arg);
    return readRobot();
}

int robotCloseCom(void)
{
    return close(fd);
}
