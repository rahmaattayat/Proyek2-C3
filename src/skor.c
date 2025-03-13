#include <stdlib.h>
#include <SDL3/SDL.h>
#include "alda.h"
#include "config.h"
#include "musuh.c"


void tambahskor(nilai *nn)
{
    nn->skor += 10;
}

void cekhighskor(nilai *nn)
{
    if (nn->skor > nn->highskor)
    {
        nn->highskor = nn->skor;
    }
}

void tampilskor(SDL_Renderer *renderer, nilai *nn) {
    // Tentukan warna untuk teks
    SDL_Color warnaTeks = { 255, 255, 255, 255 }; // Putih

    // Siapkan teks untuk skor dan high skor
    char teksSkor[50];
    char teksHighSkor[50];
    snprintf(teksSkor, sizeof(teksSkor), "Skor: %d", nn->skor);
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", nn->highskor);

    // Tentukan posisi teks
    float posXSkor = 10;
    float posYSkor = 10;
    float posXHighSkor = 10;
    float posYHighSkor = 50;

    // Gambar teks skor dengan ukuran lebih besar
    SDL_SetRenderDrawColor(renderer, warnaTeks.r, warnaTeks.g, warnaTeks.b, warnaTeks.a);
    SDL_RenderDebugText(renderer, posXSkor, posYSkor, teksSkor);
    SDL_RenderDebugText(renderer, posXHighSkor, posYHighSkor, teksHighSkor);
}