#include "Rahma.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>

void bikinMusuh(Musuh *musuh, int aktif, int tinggi, int lebar)
{
    for (int i = 0; i < JUMLAH; i++)
    {
        musuh[i].x = LEBAR_LAYAR;
        musuh[i].y = rand() % TINGGI_LAYAR;
        musuh[i].w = 50;
        musuh[i].h = 40;
        musuh[i].dx = -2.5f;
        musuh[i].batasKiri = -50;
        musuh[i].aktif = 1;
    }
}

void gerakinMusuh(Musuh musuh[])
{
    for (int i = 0; i < JUMLAH; i++)
    {
        if (musuh[i].aktif)
        { // Hanya gerakkan musuh yang aktif
            musuh[i].x += musuh[i].dx;

            // Jika musuh keluar dari layar, reset posisinya
            if (musuh[i].x + musuh[i].w < musuh[i].batasKiri)
            {
                musuh[i].x = LEBAR_LAYAR;
                musuh[i].y = rand() % TINGGI_LAYAR;
            }
        }
    }
}

void bikinGambarMusuh(SDL_Renderer *renderer, Musuh musuh[])
{
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);

    for (int i = 0; i < JUMLAH; i++)
    {
        if (musuh[i].aktif)
        {
            SDL_FRect kotakMusuh = {musuh[i].x, musuh[i].y, musuh[i].w, musuh[i].h};
            SDL_RenderFillRect(renderer, &kotakMusuh);
        }
    }
}
