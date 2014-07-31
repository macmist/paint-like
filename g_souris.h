/*permet de gerer la souris : faire les formes, verifier les collisions entre souris et fenetre */

#ifndef G_SOURIS_H_INCLUDED
#define G_SOURIS_H_INCLUDED

    /*les dessins*/
    void cercle_s(Input *in, Uint32 color, Ecran ecr[],int n_ecr, int px, Bouton bout[] , Bouton plusmoin[], Compteur compt[]);
    void vecteur_s(Input *in, Uint32 color, Ecran ecr[],int n_ecr, int px, Bouton bout[] , Bouton plusmoin[], Compteur compt[]);
    void rectangle_s(Input *in, Uint32 color, Ecran ecr[],int n_ecr, int px, Bouton bout[] , Bouton plusmoin[], Compteur compt[]);
    void rempli_s(Input *in, SDL_Surface *ecran, Uint32 color);

    /*le reste*/
    int collision (Input *in, SDL_Rect *surface);

#endif
