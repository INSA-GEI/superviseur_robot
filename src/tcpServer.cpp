#include "tcpServer.h"


std::string serverReceive(int size);
int serverSend(const void *data,int dataLength);

using namespace std;

SOCKADDR_IN ssin;
SOCKET sock;
socklen_t recsize = sizeof(ssin);

/*Socket et contexte d'adressage du client */
SOCKADDR_IN csin;
SOCKET csock;
socklen_t crecsize = sizeof(csin);

int sock_err;


// SERVER OPEN //

int serverOpen(int PORT)
{
    /* Création d'une socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    int enable = 1;

    /* Si la socket est valide */
    if(sock != INVALID_SOCKET)
    {
        printf("Socket : %d is now open using TCP/IP mod\n", sock);
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

        /* Configuration */
        ssin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
        ssin.sin_family = AF_INET;                 /* Protocole familial (IP) */
        ssin.sin_port = htons(PORT);               /* Listage du port */
        sock_err = bind(sock, (SOCKADDR*)&ssin, recsize);

        /* Si la socket fonctionne */
        if(sock_err != SOCKET_ERROR)
        {
            /* Démarrage du listage (mode server) */
            sock_err = listen(sock, 1);
            printf("Loading ... \n");

            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                /* Attente pendant laquelle le client se connecte */
                printf("Waiting for client %d ... \n",PORT);
                csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
                printf("Client Connected\n");
                return 0;
            }
            else
            {
                perror("listen");
            }
        }
        else
        {
            perror("bind");
            return(-1);
        }

    }
    else
    {
        perror("socket");
        return(-1);
    }

    return 0;
}

int lolReceive(char *data)
{
    int result;
    result = recv(csock, data, 20,0);
    //cout <<"Data : " << data << endl;

    return result;
}

int serverSend(const void *data,int dataLength)
{
    if( send(csock , data , dataLength, 0) != dataLength)
    {
        perror("Send failed : ");
        return false;
    }

    return true;
}

// SERVER CLOSE //

int serverClose(void)
{
    /* Fermeture de la socket client et de la socket serveur */
    close(csock);
    close(sock);

    printf("TCP Server Close\n");

    return 0;
}

int sendToUI(char* typeMessage, const void * data)
{
    if((string)typeMessage == IMG)
    {
       Jpg * imgC = (Jpg*)data;
        serverSend("IMG",3);
        serverSend(imgC->data(),imgC->size());
        serverSend("TRAME",5);
        return 0;
    }
    else if ((string)typeMessage == "POS")
    {
        char buffer[20];
        position * maPosition = (position*)data;
        sprintf(buffer,"POScenter: %3d;%3d | %.1fTRAME", maPosition->center.x,maPosition->center.y, maPosition->angle);
        serverSend(buffer, strlen(buffer));
        return 0;
    }
    else if ((string)typeMessage == "MES")
    {
        char buffer[50];
        sprintf(buffer, "MSG%sTRAME",(const char*)data);
        serverSend(buffer,strlen(buffer));
        return 0;
    }
    else if ((string)typeMessage == "ACK")
    {
        char buffer[50];
        sprintf(buffer, "ACK%sTRAME",(const char*)data);
        serverSend(buffer,strlen(buffer));
        return 0;
    }
    else if ((string)typeMessage == BAT)
    {
    	char buffer[50];
		sprintf(buffer, "BAT%sTRAME",(const char*)data);
		serverSend(buffer,strlen(buffer));
		return 0;
    }
    else
    {
        return -1;
    }
}

int receptionFromUI(char *typeMessage, char *data)
{
    char buffer[20];
    int tBuffer = lolReceive(buffer);
    sscanf(buffer,"%3s:%s %*s", typeMessage, data);
    return tBuffer;
}
