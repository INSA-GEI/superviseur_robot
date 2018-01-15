/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.h
 * Author: pehladik
 *
 * Created on 15 janvier 2018, 12:50
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/mutex.h>
#include <alchemy/sem.h>
#include <alchemy/queue.h>

#include "../../src/monitor.h"    
#include "../../src/robot.h"
#include "../../src/image.h"

extern RT_TASK tServeur;
extern RT_TASK tconnect;
extern RT_TASK tmove;
extern RT_TASK tenvoyer;

extern RT_MUTEX mutexEtat;
extern RT_MUTEX mutexMove;

extern RT_SEM semConnecterRobot;

extern RT_QUEUE queueMsgGUI;

extern int etatCommMoniteur;
extern int etatCommRobot;

extern int MSG_QUEUE_SIZE;

extern int PRIORITY_TSERVEUR;
extern int PRIORITY_TCONNECT;
extern int PRIORITY_TMOVE;
extern int PRIORITY_TENVOYER;

void connecter(void * arg);
void communiquer(void *arg);
void deplacer(void *arg);
void envoyer(void *arg);


#endif /* FUNCTIONS_H */

