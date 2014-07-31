/*tous ce qui touche au dessin, du pixel jusqu'a la forme*/

#ifndef DESSINS_H_INCLUDED
#define DESSINS_H_INCLUDED

#include <math.h>
#include <time.h>
#include <assert.h>
#include "VerifFonctions.h"
#include "main.h"
#include "interface.h"
#include "g_souris.h"

#include "piles.h"

    #define NO_FLAG 0
    #define HORIZONTAL 1
    #define VERTICAL 2
    #define DIAGONAL 4
    #define PI 3.14
    #define PX_MIN 2
    #define PX_MAX 20



    typedef enum /*permet de choisir quelle forme on tracera */
    {
        CERCLE, LIGNE , RECTANGLE , PINCEAU , REMPLISSAGE , PIPETTE
    }Outil;

    typedef struct
    {
        Position point;
        float dirx;
        float diry;
    }Vecteur;


    /*fonctions agissant directement sur le pixel*/
    void dessineP(int x, int y, Uint32 color, SDL_Surface *map);
    Uint32 couleurP(int xe, int ye,SDL_Surface *ecran);
    void associeRGB (Uint32 px, Compteur compt[] , SDL_Surface *surface);

    /*fonctions permettant de tracer des formes*/
    void dessineVect(Vecteur *a , int px,  Uint32 color, SDL_Surface *ecran);
    void dessineArc(int x0, int y0, int rayon, double theta, Uint32 color, SDL_Surface *map);
    void dessineRect (Position P0, double longueur, double hauteur, int px, Uint32 color , SDL_Surface *ecran);
    void dessineCercle (Position P0 , double rayon , Uint32 color, SDL_Surface *map, int px);
    void rempliEcr(SDL_Surface* Screen, Uint32 color);
    void point (SDL_Surface* ecran, int x, int y, int px, Uint32 color);
    void remplir( SDL_Surface *surface, int x, int y, Uint32 couleur );
    int PxDansEcr (int x, int y, SDL_Surface *ecran);




#endif
