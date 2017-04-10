#include "../src/serial.h"



/*
 * robotCmd return 0 if  the cmd is received and understood.
 * -1 for a bad argument; -2 for a bad command ; -3 for a timedOut; -4 for a checkSum error
 */

int main() {
   robotOpenCom();
   printf("Resultat commande : %d \n",robotCmd(WITHOUT_WD));
   printf("Resultat commande : %d \n",robotCmd(SETMOVE,"+500"));
   printf("Resultat commande : %d \n",robotCmd(SETTURN,"-180"));
   robotCloseCom();



   return 0;
}
