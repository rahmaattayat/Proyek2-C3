#include "ihsan.h"
#include "config.h"
#include <SDL3/SDL.h>

void bikinPesawat(Pesawat *pesawat)
{
    pesawat->x = 50;
    pesawat->y = TINGGI_LAYAR / 2;
    pesawat->w = 60;
    pesawat->h = 40;
    pesawat->dx = 0;
    pesawat->dy = 0;
    pesawat->cd_tembak = 0;

    for (int i = 0; i < MAX_PELURU; i++)
    {
        pesawat->peluru[i].nyala = false;
    }
}

void gerakinPesawat(Pesawat *pesawat, const Uint8 *keyboard, bool pencetSpasi)
{
    pesawat->dx = 0;
    pesawat->dy = 0;
    float speed = 6.0f;

    if (keyboard[SDL_SCANCODE_W])
    {
        pesawat->dy = -speed;
    }
    if (keyboard[SDL_SCANCODE_S])
    {
        pesawat->dy = speed;
    }
    if (keyboard[SDL_SCANCODE_A])
    {
        pesawat->dx = -speed;
    }
    if (keyboard[SDL_SCANCODE_D])
    {
        pesawat->dx = speed;
    }
    if (pencetSpasi && pesawat->cd_tembak <= 0)
    {
        nembak(pesawat);
        pesawat->cd_tembak = 25; // cd peluru
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
    // dapetin tengahan
    float tengahX = pesawat->x + pesawat->w / 2;
    float tengahY = pesawat->y + pesawat->h / 2;

    SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);

    SDL_RenderLine(renderer,
                   pesawat->x + pesawat->w, tengahY,
                   pesawat->x, tengahY - pesawat->h / 2);

    SDL_RenderLine(renderer,
                   pesawat->x, tengahY - pesawat->h / 2,
                   pesawat->x, tengahY + pesawat->h / 2);

    SDL_RenderLine(renderer,
                   pesawat->x, tengahY + pesawat->h / 2,
                   pesawat->x + pesawat->w, tengahY);
}