/**
 * \file      imagerie.h
 * \author    L.Senaneuch
 * \version   1.0
 * \date      06/06/2017
 * \brief     Fonctions de traitement d'image utilisable pour la détection du robot.
 *
 * \details   Ce fichier utilise la libraire openCV2 pour faciliter le traitement d'image dans le projet Destijl.
 *            Il permet de faciliter la détection de l'arène et la détection du robot.
 *			  /!\ Attention Bien que celui-ci soit un .cpp la structure du code n'est pas sous forme d'objet.
 */


#ifndef IMAGERIE_H
#define IMAGERIE_H
#include <raspicam/raspicam_cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <math.h>

#define WIDTH 640 //1280 1024 640
#define HEIGHT 480 // 960 768 480

using namespace std;
using namespace cv;
using namespace raspicam;

typedef Mat Image;
typedef RaspiCam_Cv Camera;
typedef Rect Arene;
typedef vector<unsigned char> Jpg;
struct  position {
    Point center;
    Point direction;
    float angle;
};


 /**
 * \brief      Détecte la position d'un robot.
 * \details    Détecte la position de triangles blanc sur une image /a imgInput passé en paramètre d'entrer.
 *             
 * \param    *imgInput       Pointeur sur l'image sur laquelle chercher la position du des robots.
 * \param    *posTriangle    Pointeur sur un tableau de position ou seront stocké les positions des triangles détectés.
 * \param    *monArene		 Pointeur de type Arène si nécessaire d'affiner la recherche (optionnel) 
 * \return    Le nombre de triangle détecté.
 */
int detectPosition(Image *imgInput, position *posTriangle, Arene * monArene = NULL);


 
 /**
 * \brief      Capture une image avec la camera passé en entrée.
 * \details    La camera doit préalablement été ouverte via \a openCamera(...)
 *             
 * \param    *Camera       Pointeur sur la camera passé en entrée.
 * \param    *monImage 	   Pointeur sur une image capturé. 
 * \return    Retourne -1 si une erreur survient.
 */
void getImg(RaspiCam_Cv *Camera, Image * monImage);




 /**
 * \brief      Détecte une arène dans une image fournis en paramètre.
 *             
 * \param    *monImage       Pointeur sur l'image d'entrée
 * \param    *rectangle 	 Pointeur sur les coordonnées du rectangles trouvé. 
 * \return    Retourne -1 si aucune arène n'est détecté. Sinon retourne 0
 */
int detectArena(Image *monImage, Arene *rectangle);


 /**
 * \brief      Ferme la camera passé en paramétre
 *             
 * \param    *Camera       Pointeur sur la camera à fermé
 */
void closeCam(Camera *Camera);


 /**
 * \brief      Dessine le plus petit rectangle contenant l'arêne
 
 * \param    *imgInput       Pointeur sur l'image d'entrée.
 * \param    *imgOutput      Pointeur sur l'image de sortie (image d'entrée + arène marqué)
 * \param    *monArene		 Pointeur de type Arène contenant les information à dessiné 
 */
void drawArena(Image *imgInput, Image *imgOutput, Arene *monArene);


 /**
 * \brief      Détecte la position d'un robot.
 * \details    Détecte la position de triangles blanc sur une image /a imgInput passé en paramètre d'entrer.
 *             
 * \param    *imgInput      	Pointeur sur l'image à sauvegarder en mémoire sous format jpg.
 * \param    *imageCompress		Pointeur sur une image .jpg prête à être envoyer à l'Interaface graphique.
 */
void imgCompress(Image *imgInput, Jpg *imageCompress);

 
 
 /**
 * \brief      Ouvre une camera.
 * \details    Met à jour le file descriptor passé en paramètre pour correspondre à la camera ouverte
 *             
 * \param    *Camera      	Pointeur d'un file descriptor d'une camera ouverte
 * \return retourne 0 si la camera a été ouverte correctement et -1 si une erreur survient.
 */
int openCamera(RaspiCam_Cv  *Camera);



 
 /**
 * \brief      Dessine sur une image en entrée la position d'un robot et sa direction.
 * \details    Sauvegarde l'image des coordonnées passé par positionRobot superposé à l'image d'entrée sur imgOutput.
 *             
 * \param      *imgInput	      	Pointeur sur l'image d'entrée
 * \param      *imgOutput    		Pointeur sur l'image de sortie ( image d'entrée + dessin de la position)
 * \param      *positionRobot   	Pointeur sur la structure position d'un robot.
 */
void drawPosition(Image *imgInput, Image *imgOutput, position *positionRobot);



#endif // IMAGERIE_H
