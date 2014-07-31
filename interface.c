/*concerne l'interface, a savoir la gestion des deplacements de fenetres, ainsi que leur etat*/
#include "dessins.h"
#include <stdarg.h>

void bougerRects(Input *in ,SDL_Surface *ecran, SDL_Surface *fenetre , SDL_Surface *rect , SDL_Rect *posFntr , SDL_Rect *posRect)/*cette fonction permet de déplacer un ensemble de 2 surfaces */
{
    double X1,X2,Y1,Y2,X3,Y3;
    X1 = in->mousex - posFntr->x; Y1 = in->mousey - posFntr->y;
    X2 = in->mousex - posRect->x; Y2 = in->mousey - posRect->y;
    X3 = posRect->x - posFntr->x; Y3 = posRect->y - posFntr->y;
    if ( in->mousebuttons[SDL_BUTTON_LEFT])
    {
        do
        {
            posFntr->x =  in->mousex - X1 ;
            posFntr->y =  in->mousey - Y1;
            posRect->x =  in->mousex - X2 ;
            posRect->y =  in->mousey - Y2;
            if (posFntr->x + posFntr->w >= ecran->w)
            {
                posFntr->x = ecran->w-posFntr->w;
                posRect->x = posFntr->x + X3;
            }
            if (posFntr->y + posFntr->h >= ecran->h)
            {
                posFntr->y = ecran->h-posFntr->h;
                posRect->y = posFntr->y + Y3;
            }
            if(posFntr->x < 0)
            {
                posFntr->x = 0;
                posRect->x = posFntr->x + X3;
            }
            if(posFntr->y < 0)
            {
                posFntr->y = 0;
                posRect->y = posFntr->y + Y3;
            }
            UpdateEvents(in);

        }while (in->mousebuttons[SDL_BUTTON_LEFT] );
    }
}

void montrerFenetre (SDL_Surface *ecran ,SDL_Surface *fenetre, SDL_Rect *posfenetre, Bouton monBouton)
{

    switch (monBouton.etat)
    {
        case ON:
           SDL_BlitSurface(fenetre,NULL,ecran,posfenetre);
           break;
        case OFF:
           break;

    }
    SDL_Flip(ecran);
}


