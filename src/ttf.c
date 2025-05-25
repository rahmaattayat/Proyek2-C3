#include "gema.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_render.h> 
#include <string.h>           
#include <stdio.h>

TTF_Font* font = NULL;

void initTTF() {
    if (TTF_Init() < 0) {
        printf("SDL_ttf initialization failed: %s\n", SDL_GetError());
        return;
    }

    font = TTF_OpenFont("assets/fonts/ChonkyBunny.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", SDL_GetError());
    }
}

void renderText(SDL_Renderer* renderer, int x, int y, const char* text, SDL_Color color) {
    if (!font || !text) return;

    size_t length = strlen(text);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, length, color);
    if (!surface) {
        printf("Text rendering failed: %s\n", SDL_GetError());
        return;
    }

    int w = surface->w;
    int h = surface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Texture creation failed: %s\n", SDL_GetError());
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect dst = {(float)x, (float)y, (float)w, (float)h};
    SDL_RenderTexture(renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void cleanupTTF() {
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}