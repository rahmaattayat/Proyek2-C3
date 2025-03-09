#include "gema.h"
#include <stdlib.h>

void bikinBackground(Background *background, int lebar, int tinggi)
{
    background->jumlah = MAKSIMAL_BINTANG;
    background->lebarLayar = lebar;
    background->tinggiLayar = tinggi;

    for (int i = 0; i < MAKSIMAL_BINTANG; i++)
    {
        float x = (float)(rand() % lebar);
        float y = (float)(rand() % tinggi);
        float size = 1.0f + (rand() % 3);
        float kecepatanBintang = 0.5f + (rand() % 3); // Kecepatan antara 0.5 hingga 3.0
        background->bintang[i] = bikinBintang(x, y, size, kecepatanBintang);
    }
}

void updateBackground(Background *background, float selisihwaktu)
{
    for (int i = 0; i < background->jumlah; i++)
    {
        background->bintang[i].x -= background->bintang[i].kecepatanBintang * selisihwaktu; // Gunakan kecepatan unik

        // Jika keluar layar, pindahkan ke kanan
        if (background->bintang[i].x < 0)
        {
            background->bintang[i].x = background->tinggiLayar;
            background->bintang[i].y = rand() % background->tinggiLayar;   // Random posisi Y baru
            background->bintang[i].kecepatanBintang = 0.5f + (rand() % 3); // Beri kecepatan baru
        }
    }
}

void renderBackground(const Background *background, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // warna putih
    for (int i = 0; i < background->jumlah; i++)
    {
        SDL_FRect starRect = {background->bintang[i].x, background->bintang[i].y, background->bintang[i].ukuranBintang, background->bintang[i].ukuranBintang};
        SDL_RenderFillRect(renderer, &starRect);
    }
}
