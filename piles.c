/*permet la gestion des piles, en particulier pour la fonction de remplissage, sur un code de GurneyH, sur le conseil de joe78, merci à eux deux */

#include "dessins.h"



/*il s'agit pour l'instant d'un copier coller du code de GurneyH, réalisé à des fins de test, je compte le reprendre "a ma sauce"
et le commenter pour le prochain update */
#define STACK_INITSIZE   1024
void Stack_delete( Stack **this )
{
    free( ( *this )->data ), ( *this )->data = NULL;
    free( *this ), *this = NULL;
}


Stack *Stack_new( void )
{
    Stack *p_new = malloc( sizeof * p_new );
    if( p_new == NULL )
    {
        fprintf( stderr, "Stack_new : not enough memory" );
        exit( EXIT_FAILURE );
    }
    p_new->data = malloc( STACK_INITSIZE * sizeof *p_new->data );

    if( p_new->data == NULL )
    {
        Stack_delete( &p_new );
        fprintf( stderr, "Stack_new : not enough memory" );
        exit( EXIT_FAILURE );
    }
    p_new->size = STACK_INITSIZE;
    p_new->nelem = 0;

    return p_new;
}


void Stack_extend( Stack **this )
{
    Pos *p_tmp = NULL;
    ( *this )->size = ( *this )->size * 2 ;
    p_tmp = realloc( ( *this )->data, ( *this )->size * sizeof *( *this )->data );
    if( p_tmp == NULL )
    {
        Stack_delete( this );
        fprintf( stderr, "Stack_extend : not enough memory" );
        exit( EXIT_FAILURE );
    }
    ( *this )->data = p_tmp;
}

void Stack_push( Stack **this, Pos data )
{
    if( ( *this )->nelem + 1 >= ( *this )->size )
        Stack_extend( this );
    ( *this )->data[( *this )->nelem++] = data;
}


Pos Stack_pop( Stack *this )
{
    Pos ret = { -1, -1};
    if( this->nelem )
    {
        ret = this->data[--this->nelem];
    }
    return ret;
}

int Stack_empty( Stack *this )
{
    return this->nelem == 0;
}

/* -------------------------------------------------------------------------- */
void putpixel( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = ( Uint8 * )surface->pixels + y * surface->pitch + x * bpp;

    switch ( bpp ) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *( Uint16 * )p = pixel;
            break;

        case 3:
            if ( SDL_BYTEORDER == SDL_BIG_ENDIAN ) {
                p[0] = ( pixel >> 16 ) & 0xff;
                p[1] = ( pixel >> 8 ) & 0xff;
                p[2] = pixel & 0xff;
            }
            else {
                p[0] = pixel & 0xff;
                p[1] = ( pixel >> 8 ) & 0xff;
                p[2] = ( pixel >> 16 ) & 0xff;
            }
            break;

        case 4:
            *( Uint32 * )p = pixel;
            break;

        default:
            break;           /* shouldn't happen, but avoids warnings */
    }
}
Uint32 getpixel( SDL_Surface *surface, int x, int y )
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = ( Uint8 * )surface->pixels + y * surface->pitch + x * bpp;

    switch ( bpp ) {
        case 1:
            return *p;

        case 2:
            return *( Uint16 * )p;

        case 3:
            if ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *( Uint32 * )p;

        default:
            return 0;
    }
}


#define N_DIR   2
 void fill( SDL_Surface *s, Sint16 x, Sint16 y, Uint32 dstclr )
{
    Pos dir[N_DIR] = {{ 0, -1}, {0, 1}};
    Uint32 srcclr = getpixel( s, x, y );
    Stack *stack = Stack_new();
    Pos p;
    p.x = x;
    p.y = y;

    if (dstclr == srcclr ) return;

    Stack_push( &stack, p );
    while( !Stack_empty(stack))
    {
        int i;
        int left, right;
        SDL_Rect rect;

        p = Stack_pop( stack );
        for( left = p.x; left >= 0; left-- )
            if( getpixel( s, left, p.y ) != srcclr )
                break;
        for( right = p.x + 1; right < s->w; right++ )
            if( getpixel( s, right, p.y ) != srcclr )
                break;

        rect.x = left;
        rect.w = right - left;
        rect.y = p.y;
        rect.h = 1;

        SDL_FillRect(s, &rect, dstclr);

        for( ; left != right; left++ )
        {
            for( i = 0; i < N_DIR; i++ )
            {
                Pos nxtp;
                nxtp.x = left;
                nxtp.y = p.y + dir[i].y;
                if( nxtp.y > 0 && nxtp.y < s->h &&nxtp.x>0
                        && getpixel( s, nxtp.x, nxtp.y ) == srcclr )
                        Stack_push( &stack, nxtp);
            }
        }
    }
    Stack_delete(&stack);
}
