/*permet la gestion des piles, en particulier pour la fonction de remplissage, sur un code de GurneyH, sur le conseil de joe78, merci à eux deux */

#ifndef PILES_H_INCLUDED
#define PILES_H_INCLUDED

    #define TAILLEINIT_PILE 1024

    typedef struct
    {
        float x, y;
    }Position;

    typedef struct
    {
        int x, y;
    } Pos;

    typedef struct
    {
        Pos *data;
        size_t size;
        size_t nelem;
    } Stack;



    void fill( SDL_Surface *s, Sint16 x, Sint16 y, Uint32 dstclr );
    Uint32 getpixel( SDL_Surface *surface, int x, int y );
    void putpixel( SDL_Surface *surface, int x, int y, Uint32 pixel );
    int Stack_empty( Stack *this );
    Pos Stack_pop( Stack *this );
    void Stack_push( Stack **this, Pos data );
    void Stack_extend( Stack **this );
    Stack *Stack_new( void );
    void Stack_delete( Stack **this );


#endif // PILES_H_INCLUDED
