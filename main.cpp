#include "serial.h"
#include "tcpServer.h"

int main() {
    serverOpen();
    robotOpenCom();

    char header[4];
    char data[20];
    memset(data, '\0',20);
    memset(header,'\0',4);
    do
    {   mesFromUI(header,data);
        if(strcmp(header, DMB) == 0)
        {
            printf("EVENEMENT DUMBER DETECTEE AVEC LE MESSAGE :%s \n",data);
            int a = robotCmd(data[0]);
            printf("Resultat CMD : %d \n", a);
            if(data[0] == 'u' && a == 0)
            {
                sendToUI(ACK);
            }
            if(data[0] == 'r' && a == 0)
            {
                sendToUI(ACK);
            }
        }

        if(strcmp(header, MES) == 0)
        {
            printf("EVENEMENT MESSAGE DETECTEE AVEC LE MESSAGE :%s \n",data);
        }

        if(strcmp(header,POS)==0)
        {
            printf("EVENEMENT POSITION DETECTEE AVEC LE MESSAGE :%s \n",data);
        }
    }while((strcmp(header,MES)!=0) || (data[0] != 'C'));
    robotCloseCom();
    serverClose();

    return 0;
}
