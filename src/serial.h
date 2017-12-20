/**
 * \file      serial.h
 * \author    L.Senaneuch
 * \version   1.0
 * \date      06/06/2017
 * \brief     Fonction permettant la communication avec le robot.
 *
 * \details   Ce fichier regroupe des fonctions facilitant la communication avec le robot en utilisant le port serie USART
 */


#ifndef DUMBERC_SERIAL_H_H
#define DUMBERC_SERIAL_H_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>


#define PING 		'p'
#define BACKIDLE 	'r'
#define WITH_WD  	'W'
#define RELOAD 		'w'
#define GETVBAT 	'v'
#define GETBUSY 	'b'
#define WITHOUT_WD 	'u'
#define SETMOVE 	'M'
#define SETTURN 	'T'
#define GOFORWARD 	'F'
#define GOBACK 		'B'
#define TURNLEFT 	'L'
#define TURNRIGHT 	'R'
#define STOPMOVE 	'S'

#define ROBOT_TIMED_OUT -3
#define ROBOT_UKNOW_CMD -2
#define ROBOT_ERROR 	-1
#define ROBOT_CHEKSUM 	-4
#define ROBOT_OK		0

#define serialPort "/dev/ttyS0"



 /**
 * \brief     Ouvre la communication avec le robot.
 * \details   Ouvre le serial port passé en paramétre. Par defaut cette fonction ouvre le port ttySO connecté au module xbee.
 *             
 * \param    *path      	 chaine de caractère indiquant le path du port serie à ouvrir.
 * \return    Return -1 si l'ouverture c'est mal passé et 0 si le port est ouvert.
 */
int robotOpenCom(const char * path=serialPort);



 /**
 * \brief      Ferme la communication avec le robot.
 * \details    Ferme le file descriptor du port serie contrôlant le robot
 *             
 * \param     void	aucun 
 * \return    Retourne -1 en cas d'erreur ou 0 en cas de fermeture effectué
 */
int robotCloseCom(void);



 /**
 * \brief      Envoi une commande au robot et attends sa réponse.
 * \details    Envoi une commande au robot en ajoutant le checksum et lis la réponse du robot en verifiant le checksum.
			   Le premier paramétre \a cmd correspond au type de commande ex : PING, SETMOVE ...
			   Le second paramétre  \a *arg correspond aux arguments à la commande ex : SETMOVE, "100"
			   La fonction retourne un code confirmation transmise par le robot (ROBOT_CHEKSUM, ROBOT_ERROR, ROBOT_TIMED_OUT, ROBOT_OK, ROBOT_UKNOW_CMD)
 *             
 * \param    cmd       Pointeur sur l'image sur laquelle chercher la position du des robots.
 * \param    *arg    Pointeur sur un tableau de position ou seront stocké les positions des triangles détectés. 
 * \return   retourne un code confirmation.
 */
int robotCmd(char cmd, char * arg=NULL);


#endif //DUMBERC_SERIAL_H_H
