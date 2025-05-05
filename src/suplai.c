#include "ihsan.h"
#include <stdlib.h>

SDL_Texture *teksturSuplaiNyawa = NULL;
SDL_Texture *teksturSuplaiAmunisi = NULL;

SuplaiNode* suplai[JENIS_SUPLAI] = {NULL, NULL};

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

int spawnSuplai(int jenis)
{
    for (int i = 0; i < MAX_SUPLAI; i++)
    {
        if (!suplai[jenis][i].aktif)
        {
            suplai[jenis][i].x = LEBAR_LAYAR;
            suplai[jenis][i].y = rand() % (TINGGI_LAYAR - 50);
            suplai[jenis][i].w = 45;
            suplai[jenis][i].h = 45;
            suplai[jenis][i].dx = -2.0 - rand() % 3;
            suplai[jenis][i].dy = 0;
            suplai[jenis][i].aktif = true;
            suplai[jenis][i].jenis = jenis;
            return 1;
        }
    }
    return 0;
}

void updateSuplai(SDL_Renderer *renderer, Pesawat *pesawat)
{
    for (int jenis = 0; jenis < JENIS_SUPLAI; jenis++)
    {
        for (int i = 0; i < MAX_SUPLAI; i++)
        {
            if (suplai[jenis][i].aktif)
            {
                suplai[jenis][i].x += suplai[jenis][i].dx;

                if (suplai[jenis][i].x < pesawat->x + pesawat->w &&
                    suplai[jenis][i].x + suplai[jenis][i].w > pesawat->x &&
                    suplai[jenis][i].y < pesawat->y + pesawat->h &&
                    suplai[jenis][i].y + suplai[jenis][i].h > pesawat->y)
                {
                    if (jenis == 0 && pesawat->nyawa < 3)
                    {
                        pesawat->nyawa++;
                    }
                    else if (jenis == 1)
                    {
                        pesawat->magasin += 5;
                        pesawat->peluru_sekarang = pesawat->magasin;
                    }
                    suplai[jenis][i].aktif = false;
                }

                if (suplai[jenis][i].x + suplai[jenis][i].w < 0)
                {
                    suplai[jenis][i].aktif = false;
                }
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
                SDL_Texture *tekstur = NULL;
                if (jenis == 0)
                {
                    tekstur = teksturSuplaiNyawa;
                }
                else
                {
                    tekstur = teksturSuplaiAmunisi;
                }

                if (tekstur)
                {
                    SDL_FRect suplaiRect = {suplai[jenis][i].x, suplai[jenis][i].y, suplai[jenis][i].w, suplai[jenis][i].h};
                    SDL_RenderTexture(renderer,tekstur, NULL, &suplaiRect);
                }
            }
        }
    }
}

SuplaiNode *buatNode(Suplai info) 
{
    SuplaiNode *node = (SuplaiNode*)malloc(sizeof(SuplaiNode));
    if (node) {
        node->info = info;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

void tambahNode(SuplaiNode** head, Suplai info) {
    SuplaiNode *node = buatNodeSuplai(info);
    if (!node) return;

    if (*head == NULL) {
        *head = node;
    } else {
        SuplaiNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
        node->prev = current;
    }
}

void hapusSemuaNode(SuplaiNode** head) {
    SuplaiNode* current = *head;
    while (current != NULL) {
        SuplaiNode* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}