#include "ihsan.h"
#include "config.h"
#include <SDL3/SDL.h>

void nembak(Pesawat *pesawat)
{
    //find peluru gaaktif
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (!pesawat->peluru[i].nyala)
        {
            pesawat->peluru[i].nyala = true;
            pesawat->peluru[i].x = pesawat->x + pesawat->w + 13;
            pesawat->peluru[i].y = pesawat->y + pesawat->h / 2;
            pesawat->peluru[i].dx = 15.0f;//kec tembak
            pesawat->peluru[i].dy = 0;
            return;//debounce
        }
    }
}

void updatePeluru(PeluruStruct *peluru)
{
    peluru->x += peluru->dx;
    peluru->y += peluru->dy;
    if (peluru->x > LEBAR_LAYAR)
    {
        peluru->nyala = false;
    }
}

void jalankanPeluru(Pesawat *pesawat)
{
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (pesawat->peluru[i].nyala)
        {
            updatePeluru(&pesawat->peluru[i]);
        }
    }
}

void bikinGambarPeluru(SDL_Renderer *renderer, Pesawat *pesawat)
{
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (pesawat->peluru[i].nyala)
        {
            //ekor peluru
            SDL_SetRenderDrawColor(renderer, 255, 200, 0, 150);//kuning ekr
            SDL_FRect ekor = {
                pesawat->peluru[i].x - 8,
                pesawat->peluru[i].y,
                pesawat->peluru[i].w, 
                pesawat->peluru[i].h
            };
            SDL_RenderFillRect(renderer, &ekor);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//reset warna
            //kotak depan
            SDL_FRect kotakpeluru = {
                pesawat->peluru[i].x,
                pesawat->peluru[i].y, 
                pesawat->peluru[i].w, 
                pesawat->peluru[i].h
            };
            SDL_RenderFillRect(renderer, &kotakpeluru);
       }
    }
}