#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#define FPS_MAX 10
    typedef struct
    {
        char key[SDLK_LAST];
        int mousex,mousey;
        int mousexrel,mouseyrel;
        char mousebuttons[8];
        char quit;
    } Input;

    typedef struct
    {
        SDL_Surface *sur;
        SDL_Rect pos;
    }Ecran;

    typedef struct
    {
        char *texte[5];
        int i;
        SDL_Surface *sur;
        SDL_Rect pos;
    }Compteur;

       typedef enum
    {
        ON,OFF
    }EBout;

    typedef struct
    {
        SDL_Surface *sur;
        EBout etat;
        SDL_Rect pos;
    }Bouton;

    void UpdateEvents(Input* in);
    void blitPdtTrace(Ecran ecr[], Bouton bout[], Bouton plusmoin[], Compteur compt[] );

#endif
