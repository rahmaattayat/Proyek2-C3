#include "ihsan.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_render.h>
#include <string.h>
#include <stdio.h>

TTF_Font *font = NULL;

void initTTF()
{
    if (TTF_Init() < 0)
    {
        printf("SDL_ttf initialization failed: %s\n", SDL_GetError());
        return;
    }

    font = TTF_OpenFont("assets/fonts/upheavtt.ttf", 24);
    if (!font)
    {
        printf("Failed to load font: %s\n", SDL_GetError());
    }
}

void getTextSize(const char *text, float scale, int *width, int *height)
{
    if (!font || !text || scale <= 0)
    {
        *width = 0;
        *height = 0;
        return;
    }
    int w, h;
    if (TTF_GetStringSize(font, text, strlen(text), &w, &h) < 0)
    {
        printf("Failed to measure text: %s\n", SDL_GetError());
        *width = 0;
        *height = 0;
        return;
    }
    *width = w * scale;
    *height = h * scale;
}

void renderText(SDL_Renderer *renderer, float x, float y, const char *text, float scale, SDL_Color color)
{
    if (!font || !text || scale <= 0)
        return;

    size_t length = strlen(text);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, length, color);
    if (!surface)
    {
        printf("Text rendering failed: %s\n", SDL_GetError());
        return;
    }

    int w = surface->w;
    int h = surface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        printf("Texture creation failed: %s\n", SDL_GetError());
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect dst = {(float)x, (float)y, (float)w * scale, (float)h * scale};
    SDL_RenderTexture(renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void cleanupTTF()
{
    if (font)
    {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}