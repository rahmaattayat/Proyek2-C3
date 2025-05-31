#include "ihsan.h"
#include "alda.h"
#include <stdlib.h>

SDL_Texture *teksturSuplaiNyawa = NULL;
SDL_Texture *teksturSuplaiAmunisi = NULL;

Suplai suplai[JENIS_SUPLAI][MAX_SUPLAI];

Uint32 waktuTerakhirSuplai = 0;
Uint32 rentangSpawnSuplai = 0;

void loadTeksturSuplai(SDL_Renderer *renderer)
{
    SDL_Surface *gambarNyawa = SDL_LoadBMP("assets/gambar/nyawa.bmp");
    if (gambarNyawa)
    {
        teksturSuplaiNyawa = SDL_CreateTextureFromSurface(renderer, gambarNyawa);
        SDL_DestroySurface(gambarNyawa);
    }
    else
    {
        SDL_Log("Gagal memuat gambar assets/gambar/nyawa.bmp: %s", SDL_GetError());
    }

    SDL_Surface *gambarAmunisi = SDL_LoadBMP("assets/gambar/amunisi.bmp");
    if (gambarAmunisi)
    {
        teksturSuplaiAmunisi = SDL_CreateTextureFromSurface(renderer, gambarAmunisi);
        SDL_DestroySurface(gambarAmunisi);
    }
    else
    {
        SDL_Log("Gagal memuat gambar assets/gambar/amunisi.bmp: %s", SDL_GetError());
    }
}

void hapusTeksturSuplai()
{
    if (teksturSuplaiNyawa)
    {
        SDL_DestroyTexture(teksturSuplaiNyawa);
        teksturSuplaiNyawa = NULL;
    }
    if (teksturSuplaiAmunisi)
    {
        SDL_DestroyTexture(teksturSuplaiAmunisi);
        teksturSuplaiAmunisi = NULL;
    }
}

void clearSuplai()
{
    for (int jenis = 0; jenis < JENIS_SUPLAI; jenis++)
    {
        for (int i = 0; i < MAX_SUPLAI; i++)
        {
            suplai[jenis][i].aktif = false;
        }
    }
}

void inisiasiSuplai(Suplai* suplai, int jenis)
{
    suplai->x = LEBAR_LAYAR;
    suplai->y = rand() % (TINGGI_LAYAR - 50);
    suplai->w = 45;
    suplai->h = 45;
    suplai->dx = -2.0 - rand() % 3;
    suplai->dy = 0;
    suplai->aktif = true;
    suplai->jenis = jenis;
}

int spawnSuplai(int jenis)
{
    for (int i = 0; i < MAX_SUPLAI; i++)
    {
        if (!suplai[jenis][i].aktif)
        {
            inisiasiSuplai(&suplai[jenis][i], jenis);
            return 1;
        }
    }
    return 0;
}

void updatePosisiSuplai(Suplai* suplai)
{
    suplai->x += suplai->dx;
    if (suplai->x + suplai->w < 0)
    {
        suplai->aktif = false;
    }
}

void cekTabrakanSuplai(Suplai* suplai, Pesawat* pesawat, int jenis)
{
    if (suplai->x >= pesawat->x + pesawat->w || suplai->x + suplai->w <= pesawat->x)
        return;
    if (suplai->y >= pesawat->y + pesawat->h || suplai->y + suplai->h <= pesawat->y)
        return;
    if (jenis == 0 && pesawat->nyawa < 3)
    {
        pesawat->nyawa++;
        playPowerUpHealthSound();
    }
    else if (jenis == 1)
    {
        pesawat->magasin += 5;
        pesawat->peluru_sekarang = pesawat->magasin;
        playPowerUpAmmoSound();
    }
    suplai->aktif = false;
}

void updateSuplai(SDL_Renderer *renderer, Pesawat *pesawat)
{
    for (int jenis = 0; jenis < JENIS_SUPLAI; jenis++)
    {
        for (int i = 0; i < MAX_SUPLAI; i++)
        {
            if (suplai[jenis][i].aktif)
            {
                updatePosisiSuplai(&suplai[jenis][i]);
                cekTabrakanSuplai(&suplai[jenis][i], pesawat, jenis);
            }
        }
    }
}

void renderSuplai(SDL_Renderer *renderer)
{
    for (int jenis = 0; jenis < JENIS_SUPLAI; jenis++)
    {
        for (int i = 0; i < MAX_SUPLAI; i++)
        {
            if (suplai[jenis][i].aktif)
            {
                SDL_Texture *tekstur = (jenis == 0) ? teksturSuplaiNyawa : teksturSuplaiAmunisi;
                if (tekstur)
                {
                    SDL_FRect suplaiRect = {suplai[jenis][i].x, suplai[jenis][i].y, suplai[jenis][i].w, suplai[jenis][i].h};
                    SDL_RenderTexture(renderer, tekstur, NULL, &suplaiRect);
                }
            }
        }
    }
}