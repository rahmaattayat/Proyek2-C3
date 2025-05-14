#include "ihsan.h"
#include <stdlib.h>

SDL_Texture *teksturSuplaiNyawa = NULL;
SDL_Texture *teksturSuplaiAmunisi = NULL;

SuplaiNode* heads[JENIS_SUPLAI] = {NULL};

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

void freeListSuplai()
{
    for (int jenis = 0; jenis < JENIS_SUPLAI; jenis++)
    {
        SuplaiNode* current = heads[jenis];
        while (current != NULL)
        {
            SuplaiNode* temp = current;
            current = current->next;
            free(temp);
        }
        heads[jenis] = NULL;
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

SuplaiNode* buatNode(int jenis)
{
    SuplaiNode* newNode = (SuplaiNode*)malloc(sizeof(SuplaiNode));
    if (!newNode)
        return NULL;
    inisiasiSuplai(&newNode->info, jenis);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void tambahNode(int jenis, SuplaiNode* node)
{
    if (!node)
        return;
    if (heads[jenis] == NULL)
    {
        heads[jenis] = node;
    }
    else
    {
        SuplaiNode* last = heads[jenis];
        while (last->next != NULL)
            last = last->next;
        last->next = node;
        node->prev = last;
    }
}

void hapusNode(int jenis, SuplaiNode* node)
{
    if (!node)
        return;
    if (node->prev)
        node->prev->next = node->next;
    else
        heads[jenis] = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node);
}

int hitungSuplaiAktif(int jenis)
{
    int count = 0;
    SuplaiNode* current = heads[jenis];
    while (current != NULL)
    {
        if (current->info.aktif)
            count++;
        current = current->next;
    }
    return count;
}

int spawnSuplai(int jenis)
{
    if (hitungSuplaiAktif(jenis) >= MAX_SUPLAI)
        return 0;
    SuplaiNode* newNode = buatNode(jenis);
    if (!newNode)
        return 0;
    tambahNode(jenis, newNode);
    return 1;
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
    }
    else if (jenis == 1)
    {
        pesawat->magasin += 5;
        pesawat->peluru_sekarang = pesawat->magasin;
    }
    suplai->aktif = false;
}

void updateSuplai(SDL_Renderer *renderer, Pesawat *pesawat)
{
    for (int jenis = 0; jenis < JENIS_SUPLAI; jenis++)
    {
        SuplaiNode* current = heads[jenis];
        while (current != NULL)
        {
            SuplaiNode* next = current->next;
            if (current->info.aktif)
            {
                updatePosisiSuplai(&current->info);
                cekTabrakanSuplai(&current->info, pesawat, jenis);
                if (!current->info.aktif)
                {
                    hapusNode(jenis, current);
                }
            }
            current = next;
        }
    }
}

void renderSuplai(SDL_Renderer *renderer)
{
    for (int jenis = 0; jenis < JENIS_SUPLAI; jenis++)
    {
        SuplaiNode* current = heads[jenis];
        while (current != NULL)
        {
            if (current->info.aktif)
            {
                SDL_Texture *tekstur = (jenis == 0) ? teksturSuplaiNyawa : teksturSuplaiAmunisi;
                if (tekstur)
                {
                    SDL_FRect suplaiRect = {current->info.x, current->info.y, current->info.w, current->info.h};
                    SDL_RenderTexture(renderer,tekstur, NULL, &suplaiRect);
                }
            }
            current = current->next;
        }
    }
}