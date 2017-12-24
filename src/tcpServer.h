//
// Created by lucien on 05/04/17.
//


#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
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

#define DEFAULT_PORT  8080
#define DEFAULT_PARITY 0

#define DEFAULT_NODEJS_PATH "/usr/bin/nodejs"
#define DEFAULT_INTERFACE_FILE "./interface.js"

#define closesocket(param) close(param)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

 /**
 * \brief    Lance nodejs .
 * \param    path    chemin de l'executable nodejs (défaut /usr/bin/nodejs)
  * \param    file  chemin du fichier de l'interface (défaut ./interface.js)
 * \return   retourne 0 si le process a été lancé et -1 sinon.
 */
int runNodejs(const char *  path = DEFAULT_NODEJS_PATH, char * file = DEFAULT_INTERFACE_FILE);

 /**
 * \brief    Tue le process exécutant nodejs.
 * \return   retourne 0 en cas de succès et -1 sinon.
 */
int killNodejs();

 /**
 * \brief      Mise en place du serveur (port 8080 par défaut).
 * \param    port    numéro du port utilisé par le serveur (8080 par défaut).
 * \return   retourne 0 si le serveur est mis en place et -1 en cas de problème.
 */
int serverOpen(int port=DEFAULT_PORT);  //public

 /**
 * \brief    Ferme le serveur.
     * \return   retourne 0 si le serveur est fermé et -1 en cas de problème.
 */
int serverClose(void); // public

 /**
 * \brief    Envoi d'un message vers l'interface graphique
* \param    typeMessage     Type du message envoyé. Les valeurs possibles sont 
  * IMG pour une image, MES pour un message à afficher dans la console, POS pour
  * la position du robot, BAT pour une valeur de la batterie et ACK pour valider
  * un message de l'interface.
  * \param  data   données associées au message. Le type de la donnée doit
  * correspondre au message : Image pour IMG, char * MES, Position pour POS, 
  * char * pour BAT et rien pour ACK. Attention, il n'y a aucune vérification
  * a posterio.
 * \return   retourne 0 si l'envoie a bien été réalisé et -1 en cas de problème.
 */
int sendToUI(const char* typeMessage, const void * data=NULL);


/**
 * \brief    Réception d'un message. La fonction est bloquante et retourne par
 * référence le type de message reçu (DMB pour un ordre au robot, ARN pour la
 * détection des arènes et POS pour un calcul de position) ainsi que les données
 * associées.
* \param    typeMessage     Type du message reçu : DMB pour un ordre au robot, 
 * ARN pour la demande de détection de l'arène, POS pour un calcul de position
 * et MSG pour un message de l'interface
  * \param  data   données associées au message reçu.
 * \return   retourne 0 la taille du message reçu ou une valeur négative si la
 * connexion est perdue.
 */
int receptionFromUI(char *typeMessage, char *data);


#endif // TCPSERVER_H
