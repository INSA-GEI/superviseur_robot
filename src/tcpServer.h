//
// Created by lucien on 05/04/17.
//

#ifndef DUMBERC_TCPSERVER_H
#define DUMBERC_TCPSERVER_H

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include "imagerie.h"

#define IMG "IMG"
#define BAT "BAT"
#define POS "POS"
#define MES "MSG" // Message directe pour Console Dumber
#define ACK "ACK" // Message d'information concernant la derniére commande
#define DMB "DMB"

#define CLOSE	'C'

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(param) close(param)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


#define DEFAULT_PORT  8080
#define DEFAULT_PARITY 0


int serverOpen(int PORT=DEFAULT_PORT);  //public


/* Close socket.
   Return 0 if no error occurs but -1
   Default assigment port is 8080
*/
int serverClose(void); // public

/*
 * def : sendToUI envoie un message à l'interface graphique.
 * Les messages sont soit une image (IMG), un message console (MES),
 * une position (POS), ou une batterie (BAT).
 * la data doit correspondre à l'élement correspondant (Attention, pas de controle).
 */
int sendToUI(char* typeMessage, const void * data=NULL);


/*
 * def : receptionFromUI est une fonction bloquante. Elle reçoit un message,
 * et retourne par référence le type du message (DMB,ARN,POS), ainsi que la data correspondante.
 * retourne la longueur de la chaine reçu.
 */
int receptionFromUI(char *typeMessage, char *data);


#endif // TCPSERVER_H


#endif //DUMBERC_TCPSERVER_H
