#include "ihsan.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include "rahma.h"

PeluruNode* buatPeluruNode()
{
    PeluruNode* newNode = (PeluruNode*)malloc(sizeof(PeluruNode));
    if (!newNode)
        return NULL;
    bikinPeluru(&newNode->info);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void tambahPeluruNode(Pesawat* pesawat, PeluruNode* node)
{
    if (!node)
        return;
    if (pesawat->peluruHead == NULL)
    {
        pesawat->peluruHead = node;
    }
    else
    {
        PeluruNode* last = pesawat->peluruHead;
        while (last->next != NULL)
            last = last->next;
        last->next = node;
        node->prev = last;
    }
}

void hapusPeluruNode(Pesawat* pesawat, PeluruNode* node)
{
    if (!node)
        return;
    if (node->prev)
        node->prev->next = node->next;
    else
        pesawat->peluruHead = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node);
}

void freePeluruList(Pesawat* pesawat)
{
    PeluruNode* current = pesawat->peluruHead;
    while (current)
    {
        PeluruNode* temp = current;
        current = current->next;
        free(temp);
    }
    pesawat->peluruHead = NULL;
}

int nembak(Pesawat* pesawat)
{
    if (pesawat->cd_tembak > 0 || pesawat->peluru_sekarang <= 0 || pesawat->sedang_reload)
        return 0;

    PeluruNode* newNode = buatPeluruNode();
    if (!newNode)
        return 0;

    newNode->info.x = pesawat->x + pesawat->w;
    newNode->info.y = pesawat->y + pesawat->h / 2 - newNode->info.h / 2;
    newNode->info.dx = 15;
    newNode->info.nyala = true;

    tambahPeluruNode(pesawat, newNode);

    pesawat->peluru_sekarang--;
    pesawat->cd_tembak = 10;
    return 1;
}

void jalankanPeluru(Pesawat* pesawat)
{
    PeluruNode* current = pesawat->peluruHead;
    while (current)
    {
        PeluruNode* next = current->next;
        if (current->info.nyala)
        {
            current->info.x += current->info.dx;
            if (current->info.x > LEBAR_LAYAR)
            {
                current->info.nyala = false;
                hapusPeluruNode(pesawat, current);
            }
        }
        current = next;
    }
}

void bikinGambarPeluru(SDL_Renderer* renderer, Pesawat* pesawat)
{
    PeluruNode* current = pesawat->peluruHead;
    while (current)
    {
        if (current->info.nyala)
        {
            SDL_SetRenderDrawColor(renderer, 255, 200, 0, 150);
            SDL_FRect ekor = {
                current->info.x - 8,
                current->info.y,
                current->info.w,
                current->info.h
            };
            SDL_RenderFillRect(renderer, &ekor);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_FRect kotakpeluru = {
                current->info.x,
                current->info.y,
                current->info.w,
                current->info.h
            };
            SDL_RenderFillRect(renderer, &kotakpeluru);
        }
        current = current->next;
    }
}

int reload(Pesawat *pesawat)
{
    if (!pesawat->sedang_reload && pesawat->peluru_sekarang < pesawat->magasin)
    {
        pesawat->sedang_reload = true;
        pesawat->waktu_reload = 60;
        return 1;
    }
    return 0;
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
    SDL_Color red = {255, 50, 50, 255};
    SDL_Color white = {255, 255, 255, 255};

    if (pesawat->sedang_reload)
    {
        renderText(renderer, 20, 640, "RELOADING...", red);
    }

    sprintf(text, "AMMO: %d/%d", pesawat->peluru_sekarang, pesawat->magasin);
    renderText(renderer, 20, 665, text, white);
}