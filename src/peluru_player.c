#include "ihsan.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include "rahma.h"

void nembak(Pesawat *pesawat)
{
    if (pesawat->peluru_sekarang <= 0 || pesawat->sedang_reload)
    {
        return;
    }

    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (!pesawat->peluru[i].nyala)
        {
            pesawat->peluru_sekarang--;
            pesawat->peluru[i].nyala = true;
            pesawat->peluru[i].x = pesawat->x + pesawat->w + 13;
            pesawat->peluru[i].y = pesawat->y + pesawat->h / 2;
            pesawat->peluru[i].dx = 15.0f; // kec tembak
            pesawat->peluru[i].dy = 0;
            playShootSound();
            return; // debounce
        }
    }
}

void jalankanPeluru(Pesawat *pesawat)
{
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (pesawat->peluru[i].nyala)
        {
            pesawat->peluru[i].x += pesawat->peluru[i].dx;
            pesawat->peluru[i].y += pesawat->peluru[i].dy;
            if (pesawat->peluru[i].x > LEBAR_LAYAR)
            {
                pesawat->peluru[i].nyala = false;
            }
        }
    }
}

void bikinGambarPeluru(SDL_Renderer *renderer, Pesawat *pesawat)
{
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (pesawat->peluru[i].nyala)
        {
            // ekor peluru
            SDL_SetRenderDrawColor(renderer, 255, 200, 0, 150); // kuning ekr
            SDL_FRect ekor = {
                pesawat->peluru[i].x - 8,
                pesawat->peluru[i].y,
                pesawat->peluru[i].w,
                pesawat->peluru[i].h};
            SDL_RenderFillRect(renderer, &ekor);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // reset warna
            // kotak depan
            SDL_FRect kotakpeluru = {
                pesawat->peluru[i].x,
                pesawat->peluru[i].y,
                pesawat->peluru[i].w,
                pesawat->peluru[i].h};
            SDL_RenderFillRect(renderer, &kotakpeluru);
        }
    }
}

void reload(Pesawat *pesawat)
{
    if (!pesawat->sedang_reload && pesawat->peluru_sekarang < pesawat->magasin)
    {
        pesawat->sedang_reload = true;
        pesawat->waktu_reload = 60;
    }
}

void updateReload(Pesawat *pesawat)
{
    if (pesawat->sedang_reload)
    {
        pesawat->waktu_reload--;
        if (pesawat->waktu_reload <= 0)
        {
            pesawat->peluru_sekarang = pesawat->magasin;
            pesawat->sedang_reload = false;
        }
    }
}

void tampilAmunisi(SDL_Renderer *renderer, Pesawat *pesawat)
{
    char text[64];

    if (pesawat->sedang_reload)
    {
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_RenderDebugText(renderer, 20, 640, "RELOADING...");
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    sprintf(text, "AMMO: %d/%d", pesawat->peluru_sekarang, pesawat->magasin);
    SDL_RenderDebugText(renderer, 20, 665, text);
}