#include "Rahma.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include "fairuz.h"
#include "alda.h"
#include "gema.h"

int jumlahmusuh = 5;

void bikinMusuh(Musuh *musuh, int jumlahmusuh, int aktif, int tinggi, int lebar)
{
    int variasi = 30;
    int jarak_musuh = 100;
    for (int i = 0; i < jumlahmusuh; i++)
    {
        musuh[i].x = LEBAR_LAYAR + i * (jarak_musuh + rand() % variasi);
        musuh[i].y = 10 + rand() % (TINGGI_LAYAR - musuh[i].h - 20);
        musuh[i].w = 65;
        musuh[i].h = 65;
        musuh[i].dx = -2.5f;
        musuh[i].batasKiri = -50;
        musuh[i].aktif = 1;
    }
}

void gerakinMusuh(Musuh musuh[])
{
    for (int i = 0; i < jumlahmusuh; i++)
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
    }
}

void nabrakPeluru(Pesawat *pesawat, Musuh musuh[])
{
    for (int i = 0; i < MAX_PELURU; i++)
    {
        if (!pesawat->peluru[i].nyala)
            continue;

        for (int j = 0; j < jumlahmusuh; j++)
        {
            if (!musuh[j].aktif)
                continue;

            // ngecek tabrakan apa ngga
            if (pesawat->peluru[i].x < musuh[j].x + musuh[j].w &&
                pesawat->peluru[i].x + 10 > musuh[j].x &&
                pesawat->peluru[i].y < musuh[j].y + musuh[j].h &&
                pesawat->peluru[i].y + 4 > musuh[j].y)
            {
                // matiin musuh kalo kena peluru
                musuh[j].aktif = 0;
                pesawat->peluru[i].nyala = false;
                //tambah skornya
                tambahskor(&point);
                cekhighskor(&point);
            }
        }
    }
}

void nabrakMusuh(SDL_Renderer *renderer,Pesawat *pesawat, Musuh musuh[])
{
    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].aktif &&
            pesawat->x < musuh[i].x + musuh[i].w && pesawat->x + pesawat->w > musuh[i].x && pesawat->y < musuh[i].y + musuh[i].h && pesawat->y + pesawat->h > musuh[i].y)
        {
            gameover(renderer, &point);
            SDL_Delay(3000);
            SDL_Quit();
            exit(0);
        }
    }
}

void bikinGambarMusuh(SDL_Renderer *renderer, Musuh musuh[]) {
    SDL_Color warnaTubuh = {50, 255, 70, 255};    // Warna hijau untuk tubuh
    SDL_Color warnaMata = {255, 50, 50, 255};     // Warna merah untuk mata
    SDL_Color warnaDetail = {200, 200, 20, 255}; // Warna kuning untuk detail

    for (int i = 0; i < jumlahmusuh; i++) {
        if (musuh[i].aktif) {
            float x = musuh[i].x;
            float y = musuh[i].y;
            float w = musuh[i].w;
            float h = musuh[i].h;

            float TengahanX = x + w / 2;
            float TengahanY = y + h / 2;

            // Kepala 
            SDL_FRect kepala = {TengahanX - w * 0.4f, y + h * 0.1f, w * 0.8f, h * 0.5f};
            SDL_SetRenderDrawColor(renderer, warnaTubuh.r, warnaTubuh.g, warnaTubuh.b, warnaTubuh.a);
            SDL_RenderFillRect(renderer, &kepala);

            // Mata 
            SDL_SetRenderDrawColor(renderer, warnaMata.r, warnaMata.g, warnaMata.b, warnaMata.a);
            SDL_FRect mataKiri = {TengahanX - w * 0.25f, y + h * 0.2f, w * 0.15f, h * 0.15f};
            SDL_FRect mataKanan = {TengahanX + w * 0.10f, y + h * 0.2f, w * 0.15f, h * 0.15f};
            SDL_RenderFillRect(renderer, &mataKiri);
            SDL_RenderFillRect(renderer, &mataKanan);

            // Antenna
            SDL_SetRenderDrawColor(renderer, warnaDetail.r, warnaDetail.g, warnaDetail.b, warnaDetail.a);
            SDL_RenderLine(renderer, TengahanX - w * 0.25f, y + h * 0.1f, TengahanX - w * 0.4f, y);
            SDL_RenderLine(renderer, TengahanX + w * 0.25f, y + h * 0.1f, TengahanX + w * 0.4f, y);

            // Lengan
            SDL_FRect tanganKiri = {x, y + h * 0.3f, w * 0.1f, h * 0.2f};
            SDL_FRect tanganKanan = {x + w * 0.9f, y + h * 0.3f, w * 0.1f, h * 0.2f};
            SDL_RenderFillRect(renderer, &tanganKiri);
            SDL_RenderFillRect(renderer, &tanganKanan);

            // Tentakel 
            SDL_FRect tentakel1 = {TengahanX - w * 0.25f, y + h * 0.6f, w * 0.1f, h * 0.2f};
            SDL_FRect tentakel2 = {TengahanX - w * 0.05f, y + h * 0.6f, w * 0.1f, h * 0.2f};
            SDL_FRect tentakel3 = {TengahanX + w * 0.15f, y + h * 0.6f, w * 0.1f, h * 0.2f};
            SDL_RenderFillRect(renderer, &tentakel1);
            SDL_RenderFillRect(renderer, &tentakel2);
            SDL_RenderFillRect(renderer, &tentakel3);

            // Mulut
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_FRect mouth = {TengahanX - w * 0.15f, y + h * 0.45f, w * 0.3f, h * 0.05f};
            SDL_RenderFillRect(renderer, &mouth);

            // Alis Mata
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderLine(renderer, TengahanX - w * 0.3f, y + h * 0.17f, TengahanX - w * 0.1f, y + h * 0.23f);
            SDL_RenderLine(renderer, TengahanX + w * 0.1f, y + h * 0.23f, TengahanX + w * 0.3f, y + h * 0.18f);
        }
    }
}