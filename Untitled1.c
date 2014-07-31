
#include "dessins.h"

void pause();
void dessineP(int x, int y, Uint32 color, SDL_Surface *map);

int main(int argc, char *argv[])
{

    SDL_Surface *ecran = NULL, *ecran_D=NULL , *fenetre_D = NULL , *deplace = NULL, *surface = NULL, *palette = NULL;
    SDL_Rect pos_F, pos_Dep, possurface, pos_EcrD,pos_Palette,pos_P2;

    Outil monoutil;
    EtatFenetre EPalette;
    Input in;
    Uint32 bleuVert,blanc ;
    int continuer,trace,px=2;


    continuer=1; trace = 0;
    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE||SDL_DOUBLEBUF);
    ecran_D = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w, ecran->h , 32, 0, 0, 0, 0);
    palette = IMG_Load("palette.png");
    fenetre_D = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, ecran->h - 2, 32, 0, 0, 0, 0); /*cette surface contiendra le menu*/
    deplace = SDL_CreateRGBSurface(SDL_HWSURFACE, 22, 18, 32, 0, 0, 0, 0);
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 22, 18, 32, 0, 0, 0, 0);
    pos_F.x = 0 + ecran->w-fenetre_D->w; pos_F.h = fenetre_D->h;
    pos_F.y = 0; pos_F.w = fenetre_D->w;
    possurface.x = pos_F.x + pos_F.w - surface->w; possurface.h = surface->h;
    possurface.y = pos_F.y ; possurface.w = surface->w;
    pos_Dep.x = possurface.x - possurface .w;
    pos_Dep.y = pos_F.y;
    pos_EcrD.x =0; pos_EcrD.y=0;
    pos_EcrD.w = ecran_D->w; pos_EcrD.h = ecran_D->h;
    pos_Palette.x = 0; pos_Palette.y = 0;


    bleuVert= SDL_MapRGB(ecran->format, 0, 0, 0);

    blanc= SDL_MapRGB(ecran->format, 255, 255, 255);
    EPalette = FERMER;




    SDL_WM_SetCaption("Peindre", NULL);

    SDL_FillRect(ecran, NULL, blanc);
    SDL_FillRect(ecran_D, NULL, blanc);
    SDL_FillRect(fenetre_D, NULL, SDL_MapRGB(ecran->format, 207, 207, 207));
    SDL_FillRect(deplace, NULL, SDL_MapRGB(ecran->format,255, 240, 35));
    SDL_FillRect(surface, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));




    memset(&in,0,sizeof(in));


    while(!in.key[SDLK_ESCAPE] && !in.quit)
    {
        UpdateEvents(&in);


        if ( in.key[SDLK_a] )
        {
            trace = 1 ; monoutil = CERCLE ;
        }
        if ( in.key[SDLK_SPACE] )
        {
            trace = 1 ; monoutil = RECTANGLE ;
        }
        if ( in.key[SDLK_l] )
        {
            trace = 1 ; monoutil = LIGNE ;
        }
        if (in.key[SDLK_RETURN]) trace = 0;
        if(in.key[SDLK_o] ) EPalette = OUVRIR;
        if(in.key[SDLK_c] ) EPalette = FERMER;
        if (EPalette == OUVRIR && collision(&in,&pos_Palette))
        {
            if(in.mousebuttons[SDL_BUTTON_LEFT])bougerRects(&in,ecran,palette,NULL,&pos_Palette,&pos_P2);
            if(in.mousebuttons[SDL_BUTTON_RIGHT]) bleuVert = couleurP(in.mousex,in.mousey,ecran);

        }

        if( in.mousebuttons[SDL_BUTTON_LEFT] && trace == 1 )
        {

            switch (monoutil)
            {
                case CERCLE :
                    cercle_s(&in , bleuVert , ecran_D,px);
                    break;
                case LIGNE :
                    vecteur_s(&in,px,bleuVert,ecran_D);
                    break;
                case RECTANGLE :
                    rectangle_s(&in,px,bleuVert,ecran_D);
                    break;
                default: break;
            }


        }
        if(collision(&in,&possurface)==1 && in.mousebuttons[SDL_BUTTON_LEFT])
        {
            rempliEcr(ecran_D,blanc);
        }
        if(!collision(&in,&pos_F) && in.mousebuttons[SDL_BUTTON_LEFT])
        {
            point(ecran_D,in.mousex,in.mousey,px,bleuVert);
        }
        if(!collision(&in,&pos_F) && !collision(&in,&pos_Palette) && in.mousebuttons[SDL_BUTTON_RIGHT])
        {
            point(ecran_D,in.mousex,in.mousey,px,blanc);
        }

        if(collision(&in,&pos_Dep)==1 && in.mousebuttons[SDL_BUTTON_LEFT])/*cette partie est à améliorer ! */
        {
            bougerRects(&in,ecran,fenetre_D, deplace,&pos_F,&pos_Dep) ;
            possurface.x = pos_Dep.x+pos_Dep.w;
            possurface.y = pos_Dep.y;

        }
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
            fill(ecran_D,in.mousex,in.mousey,bleuVert);
            in.mousebuttons[SDL_BUTTON_MIDDLE] = 0;

        }


            SDL_BlitSurface(ecran_D,NULL,ecran,&pos_EcrD);
            SDL_BlitSurface(fenetre_D, NULL, ecran, &pos_F); // Collage de la surface sur l'écran
            SDL_BlitSurface(deplace, NULL, ecran, &pos_Dep); // Collage de la surface sur l'écran
            SDL_BlitSurface(surface,NULL,ecran,&possurface);
            montrerFenetre(ecran,palette,&pos_Palette,EPalette);
            SDL_Flip (ecran);



    }


     SDL_FreeSurface(fenetre_D);
     SDL_FreeSurface(deplace);
     SDL_FreeSurface(surface);
     SDL_FreeSurface(palette);

    SDL_Quit();

    return EXIT_SUCCESS;
}

void UpdateEvents(Input* in)
{
	SDL_Event event;
        in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
        in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;

	while(SDL_PollEvent(&event))
	{
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
	}
}
