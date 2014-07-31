/*permet de gerer la souris : faire les formes, verifier les collisions entre souris et fenetre */

#include "dessins.h"

void cercle_s(Input *in, Uint32 color, Ecran ecr[],int n_ecr, int px,Bouton bout[], Bouton plusmoin[], Compteur compt[] )
{
    Ecran tmp;
    int i =0;
    double x1,y1,rayon,xint,yint;
    Position P0;
    /*conditions initiales : le centre du cercle */
    P0.x=in->mousex;
    P0.y=in->mousey;
    xint=P0.x;
    yint=P0.y;
    tmp.pos = ecr[n_ecr].pos;
    tmp.sur = SDL_CreateRGBSurface(SDL_HWSURFACE, ecr[0].sur->w, ecr[0].sur->h , 32, 0, 0, 0, 0);


    do /*ce qu'il y a dans le do while apres le updatevents permet d'afficher le cercle à chaque tour de boucle*/
    {
        UpdateEvents(in);
        x1=in->mousex;
        y1=in->mousey;
        if(x1-xint!=0 || y1-yint !=0){
        rayon = sqrt((P0.x-x1)*(P0.x-x1) + (P0.y-y1)*(P0.y-y1));

        SDL_FillRect(tmp.sur, NULL, SDL_MapRGB(tmp.sur->format, 207, 207, 207));

        SDL_SetColorKey(tmp.sur, SDL_SRCCOLORKEY, SDL_MapRGB(tmp.sur->format, 207, 207, 207));
        SDL_BlitSurface(ecr[1].sur,NULL,tmp.sur,&ecr[1].pos);
        dessineCercle(P0,rayon,color,tmp.sur,px);
        SDL_BlitSurface(tmp.sur,NULL,ecr[0].sur,&tmp.pos);



            blitPdtTrace(ecr,bout,plusmoin,compt);
        SDL_Flip(SDL_GetVideoSurface());
        }
        xint= x1; yint = y1;

    }while(in->mousebuttons[SDL_BUTTON_LEFT]);

    /*on prend les coordonnées finales et on calcule le rayon, puis on dessin*/

    x1=in->mousex;
    y1=in->mousey;
    rayon = sqrt((P0.x-x1)*(P0.x-x1) + (P0.y-y1)*(P0.y-y1));
    dessineCercle(P0,rayon,color,ecr[n_ecr].sur,px);

    SDL_BlitSurface(ecr[n_ecr].sur,NULL,SDL_GetVideoSurface(),&ecr[n_ecr].pos);
    SDL_Flip(SDL_GetVideoSurface());
    SDL_FreeSurface(tmp.sur);
    return;
}

void vecteur_s(Input *in, Uint32 color, Ecran ecr[],int n_ecr, int px,Bouton bout[], Bouton plusmoin[], Compteur compt[])
{
    Vecteur Souris;
    Ecran tmp;

    tmp.sur= SDL_CreateRGBSurface(SDL_HWSURFACE, ecr[0].sur->w, ecr[0].sur->h , 32, 0, 0, 0, 0);
    tmp.pos = ecr[n_ecr].pos;

    if(in->mousebuttons[SDL_BUTTON_LEFT])
    {
        /* position initiale, origine du vecteur */
       Souris.point.x= in->mousex; Souris.point.y=in->mousey;

        do
        {
            UpdateEvents(in);

            Souris.dirx= in->mousex - Souris.point.x ; Souris.diry=(in->mousey - Souris.point.y);
            SDL_FillRect(tmp.sur, NULL, SDL_MapRGB(tmp.sur->format, 207, 207, 207));
            SDL_SetColorKey(tmp.sur, SDL_SRCCOLORKEY, SDL_MapRGB(tmp.sur->format, 207, 207, 207));
            SDL_BlitSurface(ecr[1].sur,NULL,tmp.sur,&ecr[1].pos);
            dessineVect(&Souris,px,color,tmp.sur);
            SDL_BlitSurface(tmp.sur,NULL,ecr[0].sur,&tmp.pos);



            blitPdtTrace(ecr,bout,plusmoin,compt);

            SDL_Flip(SDL_GetVideoSurface());


        }while (in->mousebuttons[SDL_BUTTON_LEFT]);

        /*coordonnes finales et dessin */
        Souris.dirx= in->mousex - Souris.point.x ; Souris.diry=(in->mousey - Souris.point.y);
        dessineVect(&Souris,px,color,ecr[n_ecr].sur);

    }
    SDL_FreeSurface(tmp.sur);
}


void rectangle_s(Input *in, Uint32 color, Ecran ecr[],int n_ecr, int px,Bouton bout[], Bouton plusmoin[], Compteur compt[])
{
    Position Souris;
    double longueur , hauteur;
    Ecran tmp;

    tmp.sur= SDL_CreateRGBSurface(SDL_HWSURFACE, ecr[0].sur->w, ecr[0].sur->h , 32, 0, 0, 0, 0);
    tmp.pos = ecr[n_ecr].pos;

    if(in->mousebuttons[SDL_BUTTON_LEFT])
    {
        /*position initiale*/
       Souris.x= in->mousex; Souris.y=in->mousey;
        do
        {
            UpdateEvents(in);
            longueur = in->mousex - Souris.x ; hauteur=(in->mousey - Souris.y);

            SDL_FillRect(tmp.sur, NULL, SDL_MapRGB(tmp.sur->format, 207, 207, 207));
            SDL_SetColorKey(tmp.sur, SDL_SRCCOLORKEY, SDL_MapRGB(tmp.sur->format, 207, 207, 207));
            SDL_BlitSurface(ecr[1].sur,NULL,tmp.sur,&ecr[1].pos);
            dessineRect(Souris,longueur,hauteur,px,color,tmp.sur);
            SDL_BlitSurface(tmp.sur,NULL,ecr[0].sur,&tmp.pos);


            blitPdtTrace(ecr,bout,plusmoin,compt);

            SDL_Flip(SDL_GetVideoSurface());

        }while (in->mousebuttons[SDL_BUTTON_LEFT]);

        /*coordonnes finales et dessin */
        longueur = in->mousex - Souris.x ; hauteur=(in->mousey - Souris.y);
        dessineRect(Souris,longueur,hauteur,px,color,ecr[n_ecr].sur);
        SDL_FreeSurface(tmp.sur);
    }
}

int collision (Input *in, SDL_Rect *surface)
{
    /*merci fvirtman pour ton tuto*/
    if (in ->mousex >= surface->x
    && in ->mousex < surface->x + surface->w
    && in ->mousey >= surface->y
    && in ->mousey < surface->y + surface->h)
       return 1;
   else
       return 0;
}

void rempli_s(Input *in, SDL_Surface *ecran, Uint32 color)
{
    int x = in->mousex, y = in -> mousey , i=0;
    Uint32 frontiere,fond;
    fond = couleurP(x,y,ecran);
    while (couleurP(x+i,y,ecran) == fond)
    {
        i++;
    }
    frontiere = couleurP(x+i,y,ecran);

}

