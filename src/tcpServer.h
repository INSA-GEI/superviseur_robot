<<<<<<< HEAD
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
/*
 * Entête de donnée*/
///@brief Indique que la donnée sera une image.
#define IMG "IMG"
///@brief Indique que la donnée sera une information batterie.
#define BAT "BAT"
///@brief Indique que la donnée sera une position position.
#define POS "POS"
///@brief Indique une donnée MSG à afficher en console, ou à traiter.
#define MES "MSG" // Message directe pour Console Dumber
///@brief Acquitement de la derniére commande (Implémenté uniquement pour verifier la connection au robot.)
#define ACK "ACK"
///@brief Message de type commande à transmettre à Dumby.
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

/**
 * @brief Ouvre un socket TCP sur le port passé en paramétre (8080 par défaut ).
 * @code{C}
 *        serverOpen();
 * @endcode
 * @code{C}
 *        serverOpen(7878);
 * @endcode
 */
int serverOpen(int PORT=DEFAULT_PORT);  //public


/** @brief Ferme le socket.
 *  @retval retourne 0 en cas de succés ou -1 en cas d'echec.
 *  @code{C}
 *          serverClose();
 *  @endcode
 */
int serverClose(void); // public

/**
 * @brief sendToUI envoie un message à l'interface graphique.
 * Les messages sont soit une image (IMG), un message console (MES),
 * une position (POS), ou une batterie (BAT).
 * la data doit correspondre au type de message (Attention, pas de controle).
 */
int sendToUI(char* typeMessage, const void * data=NULL);


/**
 * @brief receptionFromUI est une fonction bloquante. Elle reçoit un message,
 * et retourne par référence le type du message (DMB,ARN,POS), ainsi que la data correspondante.
 * @note Pour l'aréne les informations sont de types messages et le contenu sera.
 * bArena => demande de selection d'arene
 * okArena => Validation d'arene 
 * noArena => non detection d'arene
 *
 * @retval retourne la longueur de la chaine reçu.
 */
int receptionFromUI(char *typeMessage, char *data);


#endif // TCPSERVER_H


#endif //DUMBERC_TCPSERVER_H
=======
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
 * une position (POS), un acquitement de connexion(ACK), ou une batterie (BAT)
 * la data doit correspondre au correspondant (Attention, pas de controle).
 */
int sendToUI(char* typeMessage, const void * data=NULL);


/*
 * def : receptionFromUI est une fonction bloquante. Elle reçoit un message,
 * et retourne par référence le type du message (DMB,MES,POS), ainsi que la data correspondante.
 * retourne la longueur de la chaine reçu.
 */
int mesFromUI(char *typeMessage, char *data);


#endif // TCPSERVER_H


#endif //DUMBERC_TCPSERVER_H
>>>>>>> 1b712e36af09fa845aef9bc3aac82cc9876312ec
