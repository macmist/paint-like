/*tous ce qui touche au dessin, du pixel jusqu'a la forme*/
#include "dessins.h"



void dessineP(int x, int y, Uint32 color, SDL_Surface *map) /*affiche un pixel de la couleur desiree sur l'ecran */
{
  if(x>0 && y>0 && x < map->w && y < map->h)
    *((Uint32*)(map->pixels) + x + y * map->w) = color;
}

Uint32 couleurP(int xe, int ye,SDL_Surface *ecran)/*recupere la couleur du pixel en xe,ye*/
{
    Uint32 * numerocase;
    numerocase= (Uint32 *)(ecran->pixels)+xe+ye*ecran->w;
    return (*numerocase);
}

void associeRGB (Uint32 px, Compteur compt[] , SDL_Surface *surface)
{
    Uint8 r ,g, b;
    int i = 0;
    SDL_GetRGB(px,surface->format,&r ,&g, &b);
    compt[0].i = (int) r;
    compt[1].i = (int) g;
    compt[2].i = (int) b;
    for (i = 0; i < 3 ; i++)
    sprintf(compt->texte, "%d" ,compt->i);
}


void dessineVect(Vecteur *a , int px,  Uint32 color, SDL_Surface *ecran)
{
    int i = 0 , result=0, absx=0,absy=0, pasx=0, pasy=0, x,y;
    x = a->point.x; y = a->point.y;
    point(ecran,x,y,px,color); /*dessine le point d'origine*/
    if(a->dirx>0) pasx = 1; else pasx =-1; /*etablit la direction*/
    if(a->diry > 0) pasy = 1; else pasy=-1; /*etablit la direction*/
    absx = abs(a->dirx); absy = abs(a->diry); /*la norme des directions represente le nombre de fois que le pas doit etre repete,
                                               mais aussi la pente du vecteur*/

    /*cas d'un vecteur vertical*/
    if(a->dirx == 0)
    {
        for (i=0; i<absy; i++)
        {
            y+=pasy; point(ecran,x,y,px,color);
        }
    }
    /* cas d'un vecteur horizontal*/
    else if(a->diry == 0)
    {
        for (i=0; i<absx; i++)
        {
            x+=pasx; point(ecran,x,y,px,color);
        }
    }

    /*cas d'une diagonale*/
    else if(absx == absy)
    {
        for (i=0; i<absy; i++)
        {
            x+=pasx; y+=pasy; point(ecran,x,y,px,color);
        }
    }

    else if (absx>absy) /*si la pente est douce */
    {
        for (i=0; i<absx; i++)
        {
            x+=pasx; result+=absy;
            if(result >= absx) {result-=absx; y+=pasy;}
            point(ecran,x,y,px,color);
        }
    }

    else  /*si la pente est forte*/
    {
        for (i=0; i<absy; i++)
        {
            y+=pasy; result+=absx;
            if(result >= absy) {result-=absy; x+=pasx;}
            point(ecran,x,y,px,color);
        }
    }

}


void dessineArc(int x0, int y0, int rayon, double theta, Uint32 color, SDL_Surface *map)
{
    double x,y,angle;
    for (angle=0; angle<=theta ; angle+=0.01 ) /*avec un pas defini, pas joli joli mais fonctionne*/
    {
        x=rayon*cos(angle) + x0;
        y=rayon*sin(angle) + y0;
        dessineP((int)x,(int)y,color,map);

    }
}

void dessineRect (Position P0, double longueur, double hauteur, int px, Uint32 color , SDL_Surface *ecran) /*fonction bien moche pour dessiner un rectangle*/
{
    Vecteur A,B,C,D; /*chacun represente l'un des cotes*/
    A.point = P0; /*le point de depart du rectangle */
    B.point.x = P0.x + longueur; /*de la*/
    B.point.y = P0.y ;
    C.point.x = B.point.x;
    C.point.y = B.point.y + hauteur;
    D.point.x = P0.x;
    D.point.y = P0.y + hauteur;/*jusque la on definit les positions des quatres angles */
    A.dirx = longueur;  B.dirx = 0;/*puis*/
    A.diry = 0;         B.diry = hauteur;
    C.dirx = -longueur; D.dirx = 0;
    C.diry = 0;         D.diry = -hauteur;/*la direction des vecteurs*/

    /*puis on affiche les vecteurs*/
    dessineVect(&A,px,color,ecran);
    dessineVect(&B,px,color,ecran);
    dessineVect(&C,px,color,ecran);
    dessineVect(&D,px,color,ecran);
    /*fin de la fonction moche*/
}

void dessineCercle (Position P0 , double rayon , Uint32 color, SDL_Surface *map, int px) /*permet de dessiner un cercle */
{
    double x,y, F,F1,F2 , nx,ny; int i;
    x=P0.x ; y = P0.y + rayon ; F = 0;

    /*on parcourt le 1er quart de cercle*/
    while (y>P0.y)
    {
        F1 = F + 2*(x-P0.x) +1 ; F2 = F - 2*(y - P0.y)+1;
        if (abs(F1) < abs(F2)) {x+=1; F=F1;}
        else {y-=1; F = F2;}
        dessineP(x,y,color,map);
       /*dessine les points du premier quart */
        nx= 2*P0.x -x ; ny = 2 * P0.y - y;

        /*dessine les points des 3 autres par symetrie*/
        dessineP(x,ny,color,map);
        dessineP(nx,y,color,map);
        dessineP(nx,ny,color,map);
    }



    /* on dessine le deux points qui ne verifiaient pas y>P0.y */
    dessineP(P0.x+rayon,P0.y,color,map);
    dessineP(P0.x-rayon,P0.y,color,map);
    dessineP(P0.x,P0.y+rayon,color,map);
    dessineP(P0.x,P0.y-rayon,color,map);

    if (px > 2) dessineCercle(P0,rayon+1,color,map,px-1);
}

void rempliEcr(SDL_Surface* ecran, Uint32 color)
{
    SDL_FillRect(ecran, NULL, color);
}


void point (SDL_Surface* ecran, int x, int y, int px, Uint32 color)
{
    int i=0;
    Position P0;
    P0.x=x;P0.y=y;
    for(i = 0 ; i < px ; i++)
    {
        dessineCercle(P0,i,color,ecran,0);
    }
}

#define N_DIR   2






int PxDansEcr (int x, int y, SDL_Surface *ecran)
{
    /*merci fvirtman pour ton tuto*/
    if ( x>=0
    && x < 0 + ecran->w
    && y >= 0
    && y < 0 + ecran->h)
       return 1;
   else
       return 0;
}

