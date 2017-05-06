#ifndef IMAGERIE_H
#define IMAGERIE_H
#include <raspicam/raspicam_cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <math.h>

///@brief WIDTH définis la largeur de l'image à envoyer
#define WIDTH 640 //1280 1024 640
///@brief HEIGHT définis la hauteur de l'image à envoyer
#define HEIGHT 480 // 960 768 480

using namespace std;
using namespace cv;
using namespace raspicam;

/**
 * @brief Définition du type Image. Originellement le type matrice sur OpenCv. C'est sous cette forme que
 * les images seront capturées.
 */
typedef Mat Image;
///@brief Définition du type Camera. Originellement RaspiCam_Cv dans raspicam_cv.
typedef RaspiCam_Cv Camera;
///@brief Définition du type Arene. Originelement Rect dans OpenCv. Cette variable sert à contenir le rectangle
typedef Rect Arene;
/**
 * @brief Definition du type Jpg originellement vector dans openCv.
 *        Les variables de ce types contiendront l'image formatée en Jpg, sous forme de tableau 1 dimension.
 */
typedef vector<unsigned char> Jpg;
struct  position {
    Point center;
    Point direction;
    float angle;
};

/**
 * @brief detectPosition detecte la position des triangles dans une image d'entrée (imgInput).
 * Il découpe également l'image en cas d'element de type Arene passé en paramètre.
 * La modification se fait sur imgOutput. La fonction retourne le nombre de triangle trouvé.
 * La position de chaque triangle est stocké dans un tableau de position passé par pointeur.
 * La position est relative à la resolution de l'image initial (640*480 par défaut)
 * @code{C}
 *       Image monImage; position positionRobot[20];
 *       detectPosition(&monImage, positionRobot);
 * @endcode
 */
int detectPosition(Image *imgInput, position *posTriangle, Arene * monArene = NULL);


/**
 * @brief getImg capture une image avec la camera passé en entrée.
 * La caméra doit avoir été ouverte. (cf openCamera)
 * @code{C}
 *       Image monImage;
 *       Camera rpiCam;
 *       openCamera(&rpiCam);
 *       getImg(&rpiCam, &monImage);
 * @endcode
 */
void getImg(RaspiCam_Cv *Camera, Image * monImage);



/**
 * @brief detectArena retourne 0 si une arene est detectée, et -1 si aucune arene n'est trouvée.
 * Les coordonnées de l'arene sont retournées par pointeur.
 * @code{C}
 *      Arene monArene;
 *      if(detectArena(&imageA, &monArene)==0)
 *      {
 *          printf("Arene detectée\n");
 *      }
 * @endcode
 */
int detectArena(Image *monImage, Arene *rectangle);


/**
 * @brief Ferme la camera passé en paramétre;
 * @code{C}
 *      closeCam(&rpiCam);
 * @endcode
 */
void closeCam(Camera *Camera);


/**
 * @brief dessine le plus petit rectangle contenant l'aréne en paramétre
 * @code{C}
 *      Image areneDessine;
 *      drawArena(&imgA, &areneDessine, &monArene);
 * @endcode
 */
void drawArena(Image *imgInput, Image *imgOutput, Arene *monArene);


/**
 * @brief compresse une image en entrée(imgInput) au format jpg de façon à ce que celle-ci soit prete à etre
 * envoyé à l'UI. L'image compressé est de type Jpg;
 * @code
 *      Jpg compress;
 *      imgCompress(&imgA, &compress);
 * @endcode
 */
void imgCompress(Image *imgInput, Jpg *imageCompress);


/**
 * @brief Ouvre la camera. Retourne 0 si celle-ci est ouverte, -1 si un erreur survient.
 * Il est necessaire de passer comme paramétre une variable de type Camera.
 * @code
 *      Camera cam;
 *      openCamera(&cam);
 * @endcode
 */
int openCamera(RaspiCam_Cv  *Camera);


/**
 * @brief Dessine une position de triangle sur une image de sortie(imgOutput);
 * @code
 *       if(detectPosition(&monImage,&monImage, positionRobot)>0)
 *          drawPosition(&imgA,&imgA,&positionRobot[0]);
 * @endcode
 */
void drawPosition(Image *imgInput, Image *imgOutput, position *positionRobot);


#endif // IMAGERIE_H
