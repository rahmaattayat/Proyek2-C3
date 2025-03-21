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

void updatePosisiPeluru(PeluruStruct *peluru)
{
    peluru->x += peluru->dx;
    peluru->y += peluru->dy;
}

void cekPeluruKeluarLayar(PeluruStruct *peluru)
{
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
            updatePosisiPeluru(&pesawat->peluru[i]);
            cekPeluruKeluarLayar(&pesawat->peluru[i]);
        }
    }
}

void gambarBadanPeluru(SDL_Renderer *renderer, PeluruStruct *peluru)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    SDL_FRect kotakpeluru = {
        peluru->x, 
        peluru->y - 2,
        15, 9
    };
    SDL_RenderFillRect(renderer, &kotakpeluru);
}

void gambarTrailPeluru(SDL_Renderer *renderer, PeluruStruct *peluru)
{
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 150);
    
    SDL_FRect ekor = {
        peluru->x - 8, 
        peluru->y - 1,
        13, 7
    };
    SDL_RenderFillRect(renderer, &ekor);
}

void bikinGambarPeluru(SDL_Renderer *renderer, Pesawat *pesawat)
{
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (pesawat->peluru[i].nyala)
        {
            gambarTrailPeluru(renderer, &pesawat->peluru[i]);
            gambarBadanPeluru(renderer, &pesawat->peluru[i]);
        }
    }
}