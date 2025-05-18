#include "gema.h"
#include <stdlib.h>

Bintang bikinBintang(float x, float y, float ukuran, float kecepatan)
{
    Bintang s;
    s.x = x;
    s.y = y;
    s.ukuranBintang = ukuran;
    s.kecepatanBintang = kecepatan;
    return s;
}

void bikinBackground(Background *background, int lebar, int tinggi)
{
    background->jumlah = MAX_BINTANG;
    background->lebarLayar = lebar;
    background->tinggiLayar = tinggi;

    for (int i = 0; i < MAX_BINTANG; i++)
    {
        float x = (float)(rand() % lebar);
        float y = (float)(rand() % tinggi);
        float ukuranBintang = 1 + (rand() % 3);
        float kecepatanBintang = 0.5f + (rand() % 3);
        background->bintang[i] = bikinBintang(x, y, ukuranBintang, kecepatanBintang);
    }
}

void updateBackground(Background *background, float selisihwaktu)
{
    for (int i = 0; i < background->jumlah; i++)
    {
        background->bintang[i].x -= background->bintang[i].kecepatanBintang * selisihwaktu;

        if (background->bintang[i].x < 0)
        {
            background->bintang[i].x = background->lebarLayar;
            background->bintang[i].y = rand() % background->tinggiLayar;
            background->bintang[i].kecepatanBintang = 0.5f + (rand() % 3);
        }
    }
}

void renderBackground(const Background *background, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < background->jumlah; i++)
    {
        SDL_FRect starRect = {background->bintang[i].x, background->bintang[i].y, background->bintang[i].ukuranBintang, background->bintang[i].ukuranBintang};
        SDL_RenderFillRect(renderer, &starRect);
    }
}
