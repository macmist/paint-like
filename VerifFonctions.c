/*a pour but de verifier le retour des fonctions usuelles relatives a la SDL
repris de on dernier projet, fait avec l'aide de SofEvans, que je remercie une fois encore */

#include "VerifFonctions.h"


#ifdef USE_SDL_H
    void my_SDL_Init ( Uint32 flags, const char* file, int line)
    {
        if ( (SDL_Init) (flags) == -1 )
        {
            fprintf ( stderr, " Impossible d'initialiser la SDL :%s\n ", SDL_GetError () );
            fprintf(stderr, " Ligne %d du fichier %s ", line, file);
            exit(EXIT_FAILURE);
        }
    }

    SDL_Surface* my_SDL_SetVideoMode (int width , int height , int bpp , Uint32 flags , const char* file , int line)
    {
        SDL_Surface* test = NULL ;

        test = (SDL_SetVideoMode) ( width , height , bpp , flags ) ;
        if ( !test )
        {
            fprintf( stderr, "Erreur lors d'un SDL_SetVideoMode : %s ", SDL_GetError () ) ;
            fprintf( stderr, " Ligne %d du fichier %s ", line , file ) ;
            exit( EXIT_FAILURE ) ;
        }
        return (test);
    }






#endif

#ifdef USE_SDL_IMAGE_H
SDL_Surface* my_IMG_Load(const char* image, const char* file, int line)
{
    SDL_Surface *ImgFile = NULL ;
    SDL_Surface* optimise = NULL ;

    ImgFile = (IMG_Load) (image) ;
     if (!ImgFile)
     {
        fprintf(stderr, "Erreur lors d'un IMG_Load : %s.\n" , SDL_GetError () ) ;
        fprintf(stderr, "Ligne %d du fichier %s.\n" , line , file ) ;
        exit (EXIT_FAILURE) ;
     }

     if (!(ImgFile->flags & SDL_SRCCOLORKEY))
    if (SDL_SetColorKey(ImgFile, SDL_SRCCOLORKEY, SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 0, 255)) == -1)
    {
      fprintf(stderr, "Erreur lors d'un appel a SDL_SetColorKey dans la fonction IMG_Load : %s.\n" , SDL_GetError () ) ;
      fprintf(stderr, "Ligne %d du fichier %s.\n" , line , file) ;
      exit (EXIT_FAILURE) ;
    }

  if (ImgFile->flags & SDL_SRCALPHA)
    optimise = SDL_DisplayFormatAlpha(ImgFile) ;
  else
    optimise = SDL_DisplayFormat(ImgFile) ;

  if (!optimise)
  {
    fprintf(stderr , "Erreur lors d'un appel a SDL_DisplayFormat[Alpha] dans la fonction IMG_Load : %s.\n" , SDL_GetError () ) ;
    fprintf(stderr, "Ligne %d du fichier %s.\n", line , file ) ;
    exit(EXIT_FAILURE) ;
  }
  SDL_FreeSurface(ImgFile) ;

  return (optimise) ;
}
#endif

#ifdef USE_SDL_TTF_H
    int my_TTF_Init (const char* file, int line)
    {
        if ( (TTF_Init) ()  )
        {
            fprintf( stderr , "Erreur lors d'un TTf_Init : %s\n" , TTF_GetError() ) ;
            fprintf( stderr , "Ligne %d du ficher %s\n" , line , file )  ;
        }
    }

    TTF_Font* my_TTF_OpenFont(const char* path, int ptsize, const char* file, int line)
    {
        TTF_Font* temp = NULL ;
        temp = ( TTF_OpenFont ) ( path , ptsize ) ;
        if ( !temp )
        {
            fprintf(stderr, "Erreur lors d'un TTF_OpenFont : %s.\n", TTF_GetError());
            fprintf(stderr, "Ligne %d du fichier %s.\n", line, file);
            exit(EXIT_FAILURE);
        }
        return (temp);
    }

#endif



#ifdef USE_FMOD_H





#endif
