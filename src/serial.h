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


/*
  def : Tente d'ouvrir un port série sur le path indiqué.
  Return 0 si tout le port a été ouvert. Return -1 sinon.
 */
int robotOpenCom(const char * path=serialPort);

/*def : Ferme le port série ouvert*/
int robotCloseCom(void);

/*def : Envoi une association commande + argument au robot.
Celui-ci retourne 0 si la commande est OK. retourne -3 en cas de timeout. -4 en cas d'erreur de checksum
-1 et -2 en cas d'erreur de commande et d'argument.
Si la commande est un état de batterie la fonction retourne 0 1 ou 2 en fonction de son etat.*/
int robotCmd(char cmd, char * arg=NULL);

/*Envoi une commande sans se soucier de la réponse.
Calcul le checksum*/
int sendCmd(char cmd, char * arg=NULL);

#endif //DUMBERC_SERIAL_H_H
