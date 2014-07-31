
#include "dessins.h"

#define NB_ECRANS 8
#define NB_BOUTONS 6

void pause();
void dessineP(int x, int y, Uint32 color, SDL_Surface *map);
void initEcrans(Ecran *ecrans[],int taille);
void associePos (Ecran *ecr , int x, int y, int h , int w);
void evolue(Ecran ecr[],Bouton bout[],TTF_Font *police);
void majBout(Bouton *bout);
void initBout(Bouton *bout,const char *chaine);
void initPosBout(Bouton *bout , int x, int y);
void blitBouts(Bouton bout[]);
void premBout (Bouton bout[]);
int verifColBout(Bouton *bout, Input *in);
void etatBout (Bouton bout[], Input *in);
void initCompteur(Compteur compt[]);
void modifCompteur(Compteur *compt, Bouton *boutp, Bouton *boutm, Input *in);




int main(int argc, char *argv[])
{

    Ecran ecr[NB_ECRANS];
    Bouton bout[NB_BOUTONS] ;
    TTF_Font *police =NULL;

    Uint32 color,blanc ;
    SDL_Color noir = {0,0,0};
    int continuer,i;
    char *chaine [50];

    continuer=1;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    police = TTF_OpenFont("jellb.ttf",20);


    ecr[0].sur = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE||SDL_DOUBLEBUF);
    ecr[1].sur = SDL_CreateRGBSurface(SDL_HWSURFACE, ecr[0].sur->w, ecr[0].sur->h , 32, 0, 0, 0, 0);
    ecr[2].sur= SDL_CreateRGBSurface(SDL_HWSURFACE, 150, ecr[0].sur->h , 32, 0, 0, 0, 0); /*cette surface contiendra le menu*/
    ecr[3].sur = SDL_CreateRGBSurface(SDL_HWSURFACE, 22, 18, 32, 0, 0, 0, 0);
    ecr[4].sur = TTF_RenderText_Solid(police, "R", noir);
    ecr[5].sur = TTF_RenderText_Solid(police, "G", noir);
    ecr[6].sur = TTF_RenderText_Solid(police, "B", noir);
    ecr[1].pos.x = 0 ; ecr[1].pos.y = 0;
    associePos(&ecr[2],ecr[0].sur->w - ecr[2].sur->w , ecr[1].pos.y , ecr[2].sur->w , ecr[2].sur->h);
    associePos(&ecr[3], ecr[0].sur -> w - ecr[3].sur->w, ecr[1].pos.y, ecr[3].sur->w, ecr[3].sur->h);
    associePos(&ecr[4], ecr[2].pos.x + 20, ecr[0].sur->h - 400 ,ecr[4].sur->w,ecr[4].sur->h);
    associePos(&ecr[5], ecr[4].pos.x + 50, ecr[0].sur->h - 400 ,ecr[5].sur->w,ecr[5].sur->h);
    associePos(&ecr[6], ecr[5].pos.x + 50, ecr[0].sur->h - 400 ,ecr[6].sur->w,ecr[6].sur->h);

    for (i=0 ; i < NB_BOUTONS ; i++)
    {
        sprintf(chaine, "sources/button_0%d.jpg",i);
        initBout(&bout[i],chaine);
        initPosBout(&bout[i],ecr[2].pos.x + 10 , ecr[2].pos.y + 20 + i * 25);
        puts(chaine);
    }

    blanc = SDL_MapRGB(ecr[0].sur->format, 255, 255, 255);

    SDL_WM_SetCaption("Peindre", NULL);

    SDL_FillRect(ecr[0].sur, NULL, blanc);
    SDL_FillRect(ecr[1].sur, NULL, blanc);
    SDL_FillRect(ecr[2].sur, NULL, SDL_MapRGB(ecr[0].sur->format, 207, 207, 207));
    SDL_FillRect(ecr[3].sur, NULL, SDL_MapRGB(ecr[0].sur->format, 255, 0, 0));



    evolue(ecr,bout,police);

    for ( i = 0 ; i < 3 ; i++)
     SDL_FreeSurface(ecr[i].sur);

     TTF_CloseFont(police);
     TTF_Quit();

    SDL_Quit();

    return EXIT_SUCCESS;
}

void evolue(Ecran ecr[],Bouton bout[], TTF_Font *police)
{

    Outil monoutil;
    Input in;
    Uint32 color,blanc ;
    int continuer,px=PX_MIN,i, tps0=0,tps1=0;
    Compteur compt[3];
    SDL_Color noir = {0,0,0};
    Bouton plusmoin[6];
    SDL_Event attendre;

    continuer = 1;


    color= SDL_MapRGB(ecr[0].sur->format, 0, 0, 0);
    blanc= SDL_MapRGB(ecr[1].sur->format, 255, 255, 255);

    premBout(bout);
    compt[0].sur = TTF_RenderText_Solid(police, "255", noir);
    compt[1].sur = TTF_RenderText_Solid(police, "255", noir);
    compt[2].sur = TTF_RenderText_Solid(police, "255", noir);
    compt[0].pos.x = ecr[4].pos.x -10 ;
    compt[1].pos.x = ecr[5].pos.x -10;
    compt[2].pos.x = ecr[6].pos.x -10;
    compt[0].pos.y = ecr[4].pos.y + 30 ;
    compt[1].pos.y = ecr[5].pos.y + 30 ;
    compt[2].pos.y = ecr[6].pos.y + 30;
    for (i=0  ; i < 3 ; i++)
    {
        compt[i].pos.w = compt[i].sur->w;
        compt[i].pos.h = compt[i].sur->h;
    }

    plusmoin[0].sur = TTF_RenderText_Solid(police, "+", noir);
    plusmoin[1].sur = TTF_RenderText_Solid(police, "-", noir);
    plusmoin[2].sur = TTF_RenderText_Solid(police, "+", noir);
    plusmoin[3].sur = TTF_RenderText_Solid(police, "-", noir);
    plusmoin[4].sur = TTF_RenderText_Solid(police, "+", noir);
    plusmoin[5].sur = TTF_RenderText_Solid(police, "-", noir);
    plusmoin[0].pos.x = ecr[4].pos.x;
    plusmoin[1].pos.x = ecr[4].pos.x;
    plusmoin[2].pos.x = ecr[5].pos.x;
    plusmoin[3].pos.x = ecr[5].pos.x;
    plusmoin[4].pos.x = ecr[6].pos.x;
    plusmoin[5].pos.x = ecr[6].pos.x;

    for (i= 0 ; i< 6 ; i+=2)
    {
        plusmoin[i].pos.y = compt[1].pos.y + 20;
        plusmoin[i+1].pos.y = compt[1].pos.y + 40;
        plusmoin[i].pos.w = plusmoin[i].sur->w;
        plusmoin[i+1].pos.w = plusmoin[i+1].sur->w;
        plusmoin[i].pos.h = plusmoin[i].sur->h;
        plusmoin[i+1].pos.h = plusmoin[i+1].sur->h;

    }

    memset(&in,0,sizeof(in));

    initCompteur(compt);


    while(!in.key[SDLK_ESCAPE] && !in.quit)
    {
        tps1 = SDL_GetTicks();
        if (tps1-tps0 > FPS_MAX){
        UpdateEvents(&in);
        tps0 = tps1;
        etatBout(bout,&in);

        compt[0].sur = TTF_RenderText_Solid(police, compt[0].texte, noir);
        compt[1].sur = TTF_RenderText_Solid(police, compt[1].texte, noir);
        compt[2].sur = TTF_RenderText_Solid(police, compt[2].texte, noir);
        color = SDL_MapRGB(ecr[0].sur->format, compt[0].i,compt[1].i, compt[2].i);

        if ( bout[2].etat == ON){  monoutil = CERCLE ; }
        if ( bout[3].etat == ON ) { monoutil = RECTANGLE ; }
        if ( bout[1].etat == ON ){ monoutil = LIGNE ;}
        if ( bout[0].etat == ON ){ monoutil = PINCEAU ;}
        if ( bout[4].etat == ON ){ monoutil = PIPETTE ;}
        if ( bout[5].etat == ON ){ monoutil = REMPLISSAGE ;}


        if( in.mousebuttons[SDL_BUTTON_LEFT] && !collision(&in,&ecr[2].pos) )
        {

            switch (monoutil)
            {
                case CERCLE :

                    cercle_s(&in , color , ecr,1,px, bout,plusmoin,compt);
                    break;
                case LIGNE :
                    vecteur_s(&in,color,ecr,1,px,bout,plusmoin,compt);
                    break;
                case RECTANGLE :

                    rectangle_s(&in,color,ecr,1,px,bout,plusmoin,compt);
                    break;
                case PINCEAU :
                        if(!collision(&in,&ecr[2].pos) && in.mousebuttons[SDL_BUTTON_LEFT])
                            point(ecr[1].sur,in.mousex,in.mousey,px,color);
                            break;

                case PIPETTE :
                        if(!collision(&in,&ecr[2].pos) && in.mousebuttons[SDL_BUTTON_LEFT])
                           {
                               color = couleurP(in.mousex , in.mousey, ecr[1].sur);
                                associeRGB(color,compt, ecr[1].sur);
                           }
                           break;
                case REMPLISSAGE :
                        if(!collision(&in,&ecr[2].pos) && in.mousebuttons[SDL_BUTTON_LEFT])
                        {fill(ecr[1].sur,in.mousex,in.mousey,color);
                        in.mousebuttons[SDL_BUTTON_MIDDLE] = 0;}
                default: break;
            }
        }


        if(!collision(&in,&ecr[3].pos)&& in.mousebuttons[SDL_BUTTON_RIGHT])
                            point(ecr[1].sur,in.mousex,in.mousey,px,blanc);


        if(in.mousebuttons[SDL_BUTTON_WHEELUP])
        {
            px += 1;
            if (px>PX_MAX) px=PX_MAX;
        }
        if(in.mousebuttons[SDL_BUTTON_WHEELDOWN])
        {
            px -= 1;
            if (px<PX_MIN) px=PX_MIN;
        }
        if(in.mousebuttons[SDL_BUTTON_MIDDLE])
        {
            fill(ecr[1].sur,in.mousex,in.mousey,color);
            in.mousebuttons[SDL_BUTTON_MIDDLE] = 0;

        }

            SDL_FillRect(ecr[3].sur, NULL, color);
            SDL_FillRect(ecr[2].sur, NULL, SDL_MapRGB(ecr[0].sur->format, 207, 207, 207));
            point(ecr[2].sur, ecr[2].sur->w / 2, compt[1].pos.y + 100,px,color);

            SDL_BlitSurface(ecr[1].sur,NULL,ecr[0].sur,&ecr[1].pos);
            SDL_BlitSurface(ecr[2].sur, NULL, ecr[0].sur, &ecr[2].pos); // Collage de la surface sur l'écran
            SDL_BlitSurface(ecr[3].sur,NULL,ecr[0].sur,&ecr[3].pos);
            SDL_BlitSurface(ecr[4].sur,NULL,ecr[0].sur,&ecr[4].pos);
            SDL_BlitSurface(ecr[5].sur,NULL,ecr[0].sur,&ecr[5].pos);
            SDL_BlitSurface(ecr[6].sur,NULL,ecr[0].sur,&ecr[6].pos);
            SDL_BlitSurface(compt[0].sur,NULL,ecr[0].sur,&compt[0].pos);
            SDL_BlitSurface(compt[1].sur,NULL,ecr[0].sur,&compt[1].pos);
            SDL_BlitSurface(compt[2].sur,NULL,ecr[0].sur,&compt[2].pos);
            modifCompteur(&compt[0],&plusmoin[0],&plusmoin[1],&in);
            modifCompteur(&compt[1],&plusmoin[2],&plusmoin[3],&in);
            modifCompteur(&compt[2],&plusmoin[4],&plusmoin[5],&in);

            for (i= 0 ; i < 3 ; i++)
                SDL_FreeSurface(compt[i].sur);
            blitBouts(bout);
            blitBouts(plusmoin);
            SDL_Flip (ecr[0].sur);
        }

    }
    for (i= 0 ; i < 3 ; i++)
        SDL_FreeSurface(compt[i].sur);
    for (i= 0 ; i < 6 ; i++)
        SDL_FreeSurface(plusmoin[i].sur);
}

void blitPdtTrace(Ecran ecr[], Bouton bout[], Bouton plusmoin[], Compteur compt[] )
{
    int i= 0;


    for (i= 2; i< 7;i++) SDL_BlitSurface(ecr[i].sur,NULL,ecr[0].sur,&ecr[i].pos);
    for (i = 0; i< 3; i++) SDL_BlitSurface(compt[1].sur,NULL,ecr[0].sur,&compt[i].pos);
    blitBouts(bout); blitBouts(plusmoin);
}

void majBout(Bouton *bout)
{
    if ( bout->etat == ON ) bout->etat = OFF;
    else bout->etat = ON;
}

void initBout(Bouton *bout,const char *chaine)
{
   bout->sur = IMG_Load(chaine);

}
void initPosBout(Bouton *bout , int x, int y)
{
     bout->pos.x = x;
     bout->pos.y = y;
     bout->pos.w = bout->sur->w;
     bout->pos.h = bout->sur->h;
}

void blitBouts(Bouton bout[])
{
    int i = 0;
    for (i = 0 ; i < NB_BOUTONS ; i++)
    {
        SDL_BlitSurface(bout[i].sur,NULL,SDL_GetVideoSurface(), &bout[i].pos);
    }
}

void UpdateEvents(Input* in)
{
        SDL_Event event;
        int continuer =1;
        in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
        in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;


	while(continuer)
	{
            SDL_WaitEvent(&event);
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    in->key[event.key.keysym.sym]=1;
                    break;
                case SDL_KEYUP:
                    in->key[event.key.keysym.sym]=0;
                    break;
                case SDL_MOUSEMOTION:
                    in->mousex=event.motion.x;
                    in->mousey=event.motion.y;
                    in->mousexrel=event.motion.xrel;
                    in->mouseyrel=event.motion.yrel;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    in->mousebuttons[event.button.button]=1;
                    break;
                case SDL_MOUSEBUTTONUP:
                        if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
                        in->mousebuttons[event.button.button]=0;
                    break;
                case SDL_QUIT:
                    in->quit = 1;
                    break;
                default:
                    break;
                }
            continuer = 0;

	}
}

void premBout (Bouton bout[])
{
    int i;
    bout[0].etat = ON;
    for (i = 1 ; i < NB_BOUTONS   ; i++)
    {
        bout[i]. etat = OFF ;
    }
}

void etatBout (Bouton bout[], Input *in)
{
    int i,j;
    for (i = 0 ; i < NB_BOUTONS ; i++)
    {
        if (verifColBout(&bout[i],in))
        {
            majBout(&bout[i]);
            switch (bout[i].etat)
            {
                case ON :
                j = 0;
                while (j < NB_BOUTONS) {if (j != i)bout[j].etat = OFF; j++;}

                break;
                case OFF :
                bout[0].etat = ON ;
                default : break;
            }
        }
    }
}

int verifColBout(Bouton *bout, Input *in)
{
    if (collision(in, &bout->pos) && in->mousebuttons[SDL_BUTTON_LEFT]) return 1; else return 0;
}

void initCompteur(Compteur compt[])
{
    int j;
    for (j = 0 ; j < 3 ; j ++)
    {
        compt[j].i = 0;
        sprintf(compt[j].texte, "%d" ,compt[j].i);
    }

}

void modifCompteur(Compteur *compt, Bouton *boutp, Bouton *boutm, Input *in)
{
       if (collision(in,&boutp->pos) && in->mousebuttons[SDL_BUTTON_LEFT]&& compt->i < 255)
        {compt->i++;}
        if (collision(in,&boutm->pos) && in->mousebuttons[SDL_BUTTON_LEFT]&& compt->i > 0)
        { compt->i--;}
        sprintf(compt->texte, "%d" ,compt->i);


}

void associePos (Ecran *ecr , int x, int y, int h , int w)
{
    ecr->pos.x = x;
    ecr->pos.y = y;
    if ( w > 0 && h > 0) {ecr->pos.w = w ; ecr -> pos. h = h;}
}

