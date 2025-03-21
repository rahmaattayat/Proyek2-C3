#include "ihsan.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>

void resetKecepatan(Pesawat *pesawat)
{
    pesawat->dx = 0;
    pesawat->dy = 0;
}

void bikinPeluru(PeluruStruct* peluru)
{
    peluru->nyala = false;
    peluru->x = 0;
    peluru->y = 0;
    peluru->dx = 0;
    peluru->dy = 0;
}

void bikinPesawat(Pesawat *pesawat)
{
    pesawat->x = 50;
    pesawat->y = TINGGI_LAYAR / 2;
    pesawat->w = 80;
    pesawat->h = 60;
    resetKecepatan(pesawat);
    pesawat->cd_tembak = 0;
    pesawat->nyawa = 3;

    for (int i = 0; i < MAX_PELURU; i++)
    {
    bikinPeluru(&pesawat->peluru[i]);
    }
}

void prosesInputGerak(Pesawat *pesawat, const Uint8 *keyboard)
{
    if (keyboard[SDL_SCANCODE_W])
    {
        pesawat->dy = -6.0f;
    }
    if (keyboard[SDL_SCANCODE_S])
    {
        pesawat->dy = 6.0f;
    }
    if (keyboard[SDL_SCANCODE_A])
    {
        pesawat->dx = -6.0f;
    }
    if (keyboard[SDL_SCANCODE_D])
    {
        pesawat->dx = 6.0f;
    }
}

void prosesInputTembak(Pesawat *pesawat, bool pencetSpasi)
{
    if (pencetSpasi && pesawat->cd_tembak <= 0)
    {
        nembak(pesawat);
        pesawat->cd_tembak = 25;
    }
}

void kurangiCooldown(Pesawat *pesawat)
{
    if (pesawat->cd_tembak > 0)
    {
        pesawat->cd_tembak--;
    }
}

void gerakinPesawat(Pesawat *pesawat, const Uint8 *keyboard, bool pencetSpasi)
{
    resetKecepatan(pesawat);
    prosesInputGerak(pesawat, keyboard);
    prosesInputTembak(pesawat, pencetSpasi);
    kurangiCooldown(pesawat);
}

void penggerakPesawat(Pesawat *pesawat)
{
    pesawat->x += pesawat->dx;
    pesawat->y += pesawat->dy;
}

void batesiGerakanPesawat(Pesawat *pesawat)
{
    if (pesawat->x < 0) pesawat->x = 0;
    if (pesawat->x + pesawat->w > LEBAR_LAYAR) pesawat->x = LEBAR_LAYAR - pesawat->w;
    if (pesawat->y < 0) pesawat->y = 0;
    if (pesawat->y + pesawat->h > TINGGI_LAYAR) pesawat->y = TINGGI_LAYAR - pesawat->h;
}

void updatePesawat(Pesawat *pesawat)
{
    penggerakPesawat(pesawat);
    batesiGerakanPesawat(pesawat);
}

void bikinGambarPesawat(SDL_Renderer *renderer, Pesawat *pesawat)
{
    gambarBadanPesawat(renderer, pesawat);
    gambarSayap(renderer, pesawat);
    gambarKokpit(renderer, pesawat);
    gambarMoncongan(renderer, pesawat);
    
    if (pesawat->dx != 0 || pesawat->dy != 0)
    {
        gambarNOS(renderer, pesawat);
    }
}

void gambarBadanPesawat(SDL_Renderer *renderer, Pesawat *pesawat)
{
    float tengahanX = pesawat->x + pesawat->w / 2;
    float tengahanY = pesawat->y + pesawat->h / 2;
    
    SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
    
    SDL_RenderLine(renderer, pesawat->x + pesawat->w, tengahanY, pesawat->x, tengahanY - pesawat->h / 2.5);
    SDL_RenderLine(renderer, pesawat->x, tengahanY - pesawat->h / 2.5, pesawat->x, tengahanY + pesawat->h / 2.5);
    SDL_RenderLine(renderer, pesawat->x, tengahanY + pesawat->h / 2.5, pesawat->x + pesawat->w, tengahanY);
    
    for (int i = 0; i < pesawat->w; i++) {
        float progres = (float)i / pesawat->w;
        float h = pesawat->h * progres;
        SDL_RenderLine(renderer, pesawat->x + i, tengahanY - h/ 2.5, pesawat->x + i, tengahanY + h / 2.5);
    }
}

void gambarSayap(SDL_Renderer *renderer, Pesawat *pesawat)
{
    float tengahanY = pesawat->y + pesawat->h / 2;
    
    SDL_SetRenderDrawColor(renderer, 50, 100, 200, 255);
    
    SDL_FRect sayapAtas = { 
        pesawat->x - pesawat->w / 4, 
        pesawat->y, 
        pesawat->w / 3, 
        pesawat->h / 4 
    };
    SDL_RenderFillRect(renderer, &sayapAtas);
    
    SDL_FRect sayapBwh = { 
        pesawat->x - pesawat->w / 4, 
        pesawat->y + pesawat->h - pesawat->h / 4, 
        pesawat->w / 3, 
        pesawat->h / 4 
    };
    SDL_RenderFillRect(renderer, &sayapBwh);
}

void gambarKokpit(SDL_Renderer *renderer, Pesawat *pesawat)
{
    float tengahanY = pesawat->y + pesawat->h / 2;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FRect kokpit = { 
        pesawat->x + pesawat->w / 2, 
        tengahanY - pesawat->h / 6, 
        pesawat->w / 5, 
        pesawat->h / 3 
    };
    SDL_RenderFillRect(renderer, &kokpit);

    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_FRect depankokpit = {
        pesawat->x + pesawat->w / 2 + 16, 
        tengahanY - pesawat->h / 6, 
        pesawat->w / 20, 
        pesawat->h / 3
    };
    SDL_RenderFillRect(renderer, &depankokpit);
}

void gambarMoncongan(SDL_Renderer *renderer, Pesawat *pesawat)
{
    float tengahanY = pesawat->y + pesawat->h / 2;
    
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_FRect knalpot = { 
        pesawat->x - pesawat->w / 8, 
        tengahanY - pesawat->h / 6, 
        pesawat->w / 10, 
        pesawat->h / 3 
    };
    SDL_RenderFillRect(renderer, &knalpot);
    
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_FRect moncong = {
        pesawat->x + pesawat->w, 
        tengahanY - pesawat->h / 12, 
        pesawat->w / 5, 
        pesawat->h / 5
    };
    SDL_RenderFillRect(renderer, &moncong);
    
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
    SDL_FRect merahujung = {
        pesawat->x + pesawat->w + 14, 
        tengahanY - pesawat->h / 12, 
        pesawat->w / 20, 
        pesawat->h / 5
    };
    SDL_RenderFillRect(renderer, &merahujung);
}

void gambarNOS(SDL_Renderer *renderer, Pesawat *pesawat)
{
    float tengahanY = pesawat->y + pesawat->h / 2;
    int offset = rand() % 6;
    
    SDL_FRect api[4];
    
    api[0].x = pesawat->x - pesawat->w / 1.3;
    api[0].y = tengahanY - pesawat->h / 3.2 + offset;
    api[0].w = pesawat->w / 2;
    api[0].h = pesawat->h / 1.5;
    
    api[1].x = pesawat->x - pesawat->w / 1.5;
    api[1].y = tengahanY - pesawat->h / 3.2 + offset;
    api[1].w = pesawat->w / 2.2;
    api[1].h = pesawat->h / 1.7;
    
    api[2].x = pesawat->x - pesawat->w / 1.7;
    api[2].y = tengahanY - pesawat->h / 3.5 + offset;
    api[2].w = pesawat->w / 2.5;
    api[2].h = pesawat->h / 1.9;

    api[3].x = pesawat->x - pesawat->w / 2.1;
    api[3].y = tengahanY - pesawat->h / 4.5 + offset;
    api[3].w = pesawat->w / 2.8;
    api[3].h = pesawat->h / 2.2;
    
    SDL_SetRenderDrawColor(renderer, 255, 50, 0, 255);
    SDL_RenderFillRect(renderer, &api[0]);
    
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderFillRect(renderer, &api[1]);
    
    SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255);
    SDL_RenderFillRect(renderer, &api[2]);
    
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
    SDL_RenderFillRect(renderer, &api[3]);
}

void tampilNyawa(SDL_Renderer *renderer, Pesawat *pesawat) {
    gambarTeksNyawa(renderer);
    
    int baseX = LEBAR_LAYAR - 50;
    int baseY = 30;
    int jarak = 30;
    int radius = 10;
    
    for (int i = 0; i < pesawat->nyawa; i++) {
        int x = baseX + (i * jarak) - 50;
        int y = baseY;
        gambarIkonNyawa(renderer, x, y, radius);
    }
}

void gambarTeksNyawa(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    SDL_RenderDebugText(renderer, LEBAR_LAYAR - 170, 26, "LIVES:");
}

void gambarIkonNyawa(SDL_Renderer *renderer, int x, int y, int radius) {
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    
    for (int w = 0; w <= radius*2; w++) {
        for (int h = 0; h <= radius*2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius*radius)) {
                SDL_RenderPoint(renderer, x + dx, y + dy);
            }
        }
    }
}