#include "ihsan.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>

void bikinPeluru(PeluruStruct *peluru)
{
    peluru->nyala = false;
    peluru->x = 0;
    peluru->y = 0;
    peluru->dx = 0;
    peluru->dy = 0;
    peluru->w = 13;
    peluru->h = 7;
}

void bikinPesawat(Pesawat *pesawat)
{
    pesawat->x = 50;
    pesawat->y = TINGGI_LAYAR / 2;
    pesawat->w = 80;
    pesawat->h = 60;
    pesawat->dx = 0;
    pesawat->dy = 0;
    pesawat->cd_tembak = 0;
    pesawat->nyawa = 3;
    pesawat->magasin = 30;
    pesawat->peluru_sekarang = pesawat->magasin;
    pesawat->sedang_reload = false;
    pesawat->waktu_reload = 60;

    for (int i = 0; i < MAX_PELURU; i++)
    {
    bikinPeluru(&pesawat->peluru[i]);
    }
}

void gerakinPesawat(Pesawat *pesawat, const Uint8 *keyboard, bool pencetSpasi)
{
    pesawat->dx = 0;
    pesawat->dy = 0;
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

    if (pencetSpasi && pesawat->cd_tembak <= 0)
    {
        nembak(pesawat);
        pesawat->cd_tembak = 15;
    }

    if (pesawat->cd_tembak > 0)
    {
        pesawat->cd_tembak--;
    }
}

void updatePesawat(Pesawat *pesawat)
{
    pesawat->x += pesawat->dx;
    pesawat->y += pesawat->dy;

    if (pesawat->x < 0) pesawat->x = 0;
    if (pesawat->x + pesawat->w > LEBAR_LAYAR) pesawat->x = LEBAR_LAYAR - pesawat->w;
    if (pesawat->y < 0) pesawat->y = 0;
    if (pesawat->y + pesawat->h > TINGGI_LAYAR) pesawat->y = TINGGI_LAYAR - pesawat->h;
}

void bikinGambarPesawat(SDL_Renderer *renderer, Pesawat *pesawat)
{
    int offset = rand() % 6;
    float tengahanY = pesawat->y + pesawat->h / 2;
    //badan
    SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
    
    SDL_RenderLine(renderer, pesawat->x + pesawat->w, tengahanY, pesawat->x, tengahanY - pesawat->h / 2.5);
    SDL_RenderLine(renderer, pesawat->x, tengahanY - pesawat->h / 2.5, pesawat->x, tengahanY + pesawat->h / 2.5);
    SDL_RenderLine(renderer, pesawat->x, tengahanY + pesawat->h / 2.5, pesawat->x + pesawat->w, tengahanY);
    
    for (int i = 0; i < pesawat->w; i++) {
        float progres = (float)i / pesawat->w;
        float h = pesawat->h * progres;
        SDL_RenderLine(renderer, pesawat->x + i, tengahanY - h/ 2.5, pesawat->x + i, tengahanY + h / 2.5);
    }
    //sayap
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
    //kokpit
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
    SDL_FRect ujungmoncong = {
        pesawat->x + pesawat->w + 14, 
        tengahanY - pesawat->h / 12, 
        pesawat->w / 20, 
        pesawat->h / 5
    };
    SDL_RenderFillRect(renderer, &ujungmoncong);
    //api
    SDL_FRect api[2][4];
    
    //[0]: saat pesawat diem
    api[0][0].x = pesawat->x - pesawat->w / 2.0;
    api[0][0].y = tengahanY - pesawat->h / 4.0 + offset;
    api[0][0].w = pesawat->w / 3.0;
    api[0][0].h = pesawat->h / 2.2;
    
    api[0][1].x = pesawat->x - pesawat->w / 2.2;
    api[0][1].y = tengahanY - pesawat->h / 4.0 + offset;
    api[0][1].w = pesawat->w / 3.5;
    api[0][1].h = pesawat->h / 2.5;
    
    api[0][2].x = pesawat->x - pesawat->w / 2.4;
    api[0][2].y = tengahanY - pesawat->h / 4.5 + offset;
    api[0][2].w = pesawat->w / 4.0;
    api[0][2].h = pesawat->h / 3.0;

    api[0][3].x = pesawat->x - pesawat->w / 2.8;
    api[0][3].y = tengahanY - pesawat->h / 5.5 + offset;
    api[0][3].w = pesawat->w / 4.5;
    api[0][3].h = pesawat->h / 3.5;
    
    //[1]: saat pesawat gerak
    api[1][0].x = pesawat->x - pesawat->w / 1.3;
    api[1][0].y = tengahanY - pesawat->h / 3.2 + offset ;
    api[1][0].w = pesawat->w / 2.0;
    api[1][0].h = pesawat->h / 1.5;
    
    api[1][1].x = pesawat->x - pesawat->w / 1.5;
    api[1][1].y = tengahanY - pesawat->h / 3.2 + offset;
    api[1][1].w = pesawat->w / 2.2;
    api[1][1].h = pesawat->h / 1.7;
    
    api[1][2].x = pesawat->x - pesawat->w / 1.7;
    api[1][2].y = tengahanY - pesawat->h / 3.5 + offset;
    api[1][2].w = pesawat->w / 2.5;
    api[1][2].h = pesawat->h / 1.9;

    api[1][3].x = pesawat->x - pesawat->w / 2.1;
    api[1][3].y = tengahanY - pesawat->h / 4.5 + offset;
    api[1][3].w = pesawat->w / 2.8;
    api[1][3].h = pesawat->h / 2.2;
    
    int mode;
        if (pesawat->dx == 0 && pesawat->dy == 0) {
        mode = 0;
    } else {
        mode = 1;
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 50, 0, 255);
    SDL_RenderFillRect(renderer, &api[mode][0]);
    
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderFillRect(renderer, &api[mode][1]);
    
    SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255);
    SDL_RenderFillRect(renderer, &api[mode][2]);
    
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
    SDL_RenderFillRect(renderer, &api[mode][3]);
}

void tampilNyawa(SDL_Renderer *renderer, Pesawat *pesawat) 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, 20, 690, "LIVES:");
    
    int baseX = 135;
    int baseY = 693;
    int jarak = 30;
    int radius = 10;
    
    for (int i = 0; i < pesawat->nyawa; i++) {
        int x = baseX + (i * jarak) - 50;
        int y = baseY;
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
}