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

/// @brief Commande de test de connexion avec le robot.
#define PING 		'p'
///@brief Demande au robot de repasser à l'état IDLE
#define BACKIDLE 	'r'
///@brief Demande au robot de passer en mode run avec le Watch Dog d'activé.
#define WITH_WD  	'W'
///@brief Demande une remise à zero du watchdog.
#define RELOAD 		'w'
///@brief Demande l'information batterie
#define GETVBAT 	'v'
///@brief Demande l'information si le robot est occupé (en mouvement) ou non.
#define GETBUSY 	'b'
///@brief Demande au robot de passer en mode run avec le Watch Dog désactivé.
#define WITHOUT_WD 	'u'
///@brief Demande d'un mouvement droit.
#define SETMOVE 	'M'
///@brief Demande d'un mouvement turn.
#define SETTURN 	'T'
///@brief Demande au robot d'avancer
#define GOFORWARD 	'F'
///@brief Demande au robot de reculer
#define GOBACK 		'B'
///@brief Demande au robot de tourner à gauche
#define TURNLEFT 	'L'
///@brief Demande au robot de tourner à droite
#define TURNRIGHT 	'R'
///@brief Stop le robot
#define STOPMOVE 	'S'


/* Constantes Retour commande*/
#define ROBOT_TIMED_OUT -3
#define ROBOT_UKNOW_CMD -2
#define ROBOT_ERROR 	-1
#define ROBOT_CHEKSUM 	-4
#define ROBOT_OK		0

/// @brief Le port série utilisé par défaut sera ttyS0 sur le GPIO de la raspberry.
#define serialPort "/dev/ttyS0"

/**
 * @brief robotOpenCom ouvre un port série dont le chemin a été passé en paramétre.
 * @note  la variable global serilaPort est passé en paramétre par défaut.
 * @retval 0 si succés ou -1 si echec
 * @code{C}
 *      robotOpenCom(); // Utilisation de la valeur par défaut.
 * @endcode
 * @code{C}
 *      robotOpenCom("/dev/ttyUSB0);
 * @endcode
 *
 */
int robotOpenCom(const char * path=serialPort);

/**
 * @brief robotClose com ferme le file descriptor qui gére le port Série.
 * @retval retourne -1 si erreur. Rerourne 0 si succés.
 * @code{C}
 *      robotOpenCom();
 * @endcode
 */
int robotCloseCom(void);

/**
 * @brief Délivre une commande robot parmis celle definis en variable global.
 * @retval valeurs retournée sont des constantes de retour commandes (cf define).
 * @note Les calculs de checkSUm se font
 * @code{C}
 *      robotCmd(SETMOVE,"+100");
 *      robotCmd(PING);
 * @endcode
 */
int robotCmd(char cmd, char * arg=NULL);

#endif //DUMBERC_SERIAL_H_H
