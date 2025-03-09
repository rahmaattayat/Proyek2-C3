#include "Rahma.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>

void bikinMusuh(Musuh *musuh, int aktif, int tinggi, int lebar)
{
    int variasi = 30;
    int jarak_musuh = 100;
    for (int i = 0; i < JUMLAH; i++)
    {
        musuh[i].x = LEBAR_LAYAR + i * (jarak_musuh + rand() % variasi);
        musuh[i].y = 10 + rand() % (TINGGI_LAYAR - musuh[i].h - 20);
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
        { 
            musuh[i].x += musuh[i].dx;

            // reset posisi musuh kalo udah keluar layar
            if (musuh[i].x + musuh[i].w < musuh[i].batasKiri)
            {
                musuh[i].x = LEBAR_LAYAR;
                musuh[i].y = 10 + rand() % (TINGGI_LAYAR - musuh[i].h - 20);
            }
        }

        if (!musuh[i].aktif)  
        {
            // spawn ulang musuh yang udh mati
            musuh[i].x = LEBAR_LAYAR;
            musuh[i].y = 10 + rand() % (TINGGI_LAYAR - musuh[i].h - 20);
            musuh[i].dx = -(2 + rand() % 3); // biar random kecepatannya
            musuh[i].aktif = 1; 
        }
    }
}

void nabrakPeluru(Pesawat *pesawat, Musuh musuh[])
{
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (!pesawat->peluru[i].nyala) continue; 

        for (int j = 0; j < JUMLAH; j++)
        {
            if (!musuh[j].aktif) continue; 

            // ngecek tabrakan apa ngga
            if (pesawat->peluru[i].x < musuh[j].x + musuh[j].w &&
                pesawat->peluru[i].x + 10 > musuh[j].x &&
                pesawat->peluru[i].y < musuh[j].y + musuh[j].h &&
                pesawat->peluru[i].y + 4 > musuh[j].y)
            {
                // matiin musuh kalo kena peluru
                musuh[j].aktif = 0;
                pesawat->peluru[i].nyala = false;
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
