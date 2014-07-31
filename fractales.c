#include "fractales.h"

void mandelbrot(SDL_Surface *ecran , Uint32 color)
{
    // on définit la zone que l'on dessine. Ici, la fractale en entière
    double x=0,y=0;
    double x1 = -2.1;
    double x2 = 0.6;
    double y1 = -1.2;
    double y2 = 1.2;
    double zoom = 200 ;// pour une distance de 1 sur le plan, on a 100 pixel sur l'image
    int iteration_max = 50;

    // on calcule la taille de l'image :
    double image_x = (x2 - x1) * zoom;
    double image_y = (y2 - y1) * zoom;
    double c_r =0,c_i=0,z_r=0,z_i=0,i,tmp;

    for (x = 0 ; x < image_x ;x++)
        {
            for(y = 0 ; y < image_y ;y++)
             {
                c_r = x / zoom + x1;
                c_i = y / zoom + y1;
                z_r = 0;
                z_i = 0;
                i = 0;

                do
                {
                        tmp = z_r;
                        z_r = z_r*z_r - z_i*z_i + c_r;
                        z_i = 2*z_i*tmp + c_i;
                        i = i+1;
                }while(z_r*z_r + z_i*z_i < 4 && i < iteration_max);

                if (i == iteration_max) dessineP((int)x,(int)y,color,ecran);
                else dessineP((int)x,(int)y,SDL_MapRGB(ecran->format, i*255/iteration_max, 0, i*255/iteration_max),ecran);

             }
        }
}



