/*concerne l'interface, a savoir la gestion des deplacements de fenetres, ainsi que leur etat*/

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED




    void bougerRects(Input *in ,SDL_Surface *ecran, SDL_Surface *fenetre , SDL_Surface *rect , SDL_Rect *posFntr , SDL_Rect *posRect);
    void montrerFenetre (SDL_Surface *ecran ,SDL_Surface *fenetre, SDL_Rect *posfenetre, Bouton monBouton);

#endif
