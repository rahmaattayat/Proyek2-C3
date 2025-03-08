#include "gema.h"
#include "config.h"
#include <stdlib.h>

void bikinBackground(Background *backgroud, int width, int height)
{
    backgroud->count = MAKSIMAL_BINTANG;
    backgroud->screenWidth = width;
    backgroud->screenHeight = height;

    for (int i = 0; i < MAKSIMAL_BINTANG; i++)
    {
        float x = (float)(rand() % width);
        float y = (float)(rand() % height);
        float ukuranBintang = 1.0f + (rand() % 3);
        float kecepatanBintang = 0.5f + (rand() % 3); // kecepatan bintang antara 0.5 hingga 3.0
        backgroud->bintang[i] = bikinBintang(x, y, ukuranBintang, kecepatanBintang);
    }
}

void updateBackground(Background *backgroud, float deltaTime)
{
    for (int i = 0; i < backgroud->count; i++)
    {
        backgroud->bintang[i].x -= backgroud->bintang[i].kecepatanBintang * deltaTime; // Gunakan kecepatanBintang unik

        // Jika keluar layar, pindahkan ke kanan
        if (backgroud->bintang[i].x < 0)
        {
            backgroud->bintang[i].x = backgroud->screenWidth;
            backgroud->bintang[i].y = rand() % backgroud->screenHeight;   // Random posisi Y baru
            backgroud->bintang[i].kecepatanBintang = 0.5f + (rand() % 3); // Beri kecepatanBintang baru
        }
    }
}

void renderBackground(const Background *backgroud, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // warna putih
    for (int i = 0; i < backgroud->count; i++)
    {
        SDL_FRect starRect = {backgroud->bintang[i].x, backgroud->bintang[i].y, backgroud->bintang[i].ukuranBintang, backgroud->bintang[i].ukuranBintang};
        SDL_RenderFillRect(renderer, &starRect);
    }
}
