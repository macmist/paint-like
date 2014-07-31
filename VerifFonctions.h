/*a pour but de verifier le retour des fonctions usuelles relatives a la SDL
repris de on dernier projet, fait avec l'aide de SofEvans, que je remercie une fois encore */



#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

    #include <stdlib.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL_image.h>
    #include <SDL/SDL_ttf.h>




    #define USE_SDL_H
    #define USE_SDL_IMAGE_H
    #define USE_SDL_TTF_H
    #define USE_FMOD_H

    #ifdef USE_SDL_H

        #define SDL_Init(flags) my_SDL_Init(flags, __FILE__, __LINE__)
        void my_SDL_Init ( Uint32 flags, const char* file, int line) ;
        #define SDL_SetVideoMode(width, height, bpp, flags) my_SDL_SetVideoMode(width, height, bpp, flags, __FILE__, __LINE__)
        SDL_Surface* my_SDL_SetVideoMode (int width , int height , int bpp , Uint32 flags , const char* file , int line) ;


    #endif

    #ifdef USE_SDL_IMAGE_H

        #define IMG_Load(path) my_IMG_Load( path , __FILE__ , __LINE__ )
        SDL_Surface* my_IMG_Load(const char* image, const char* file, int line) ;
    #endif

    #ifdef USE_SDL_TTF_H
        #define TTF_Init() my_TTF_Init( __FILE__ , __LINE__ )
        int my_TTF_Init (const char* file, int line) ;
        #define TTF_OpenFont( file , size ) my_TTF_OpenFont( file , size , __FILE__ , __LINE__ )
        TTF_Font* my_TTF_OpenFont(const char* path, int ptsize, const char* file, int line) ;
    #endif


    #ifdef USE_FMOD_H

    #endif


#endif
