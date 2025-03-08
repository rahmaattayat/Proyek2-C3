#include "Rahma.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>

void bikinMusuh(Musuh musuh[], int lebar, int tinggi) {
    for (int i = 0; i < JUMLAH; i++) {
        musuh[i].x = LEBAR_LAYAR;
        musuh[i].y = rand() % TINGGI_LAYAR;
        musuh[i].w = 50;
        musuh[i].h = 40;
        musuh[i].dx = -2.5f;
        musuh[i].batasKiri = -50;       
        musuh[i].aktif = 1;
    }
}

void gerakinMusuh(Musuh* musuh) {
    // Gerak horizontal (maju ke kiri)
    musuh->x += musuh->dx;

    // Jika musuh keluar dari layar, reset ke posisi awal dengan y random
    if (musuh->x + musuh->w < musuh->batasKiri) {
        musuh->x = LEBAR_LAYAR;
        musuh->y = rand() % TINGGI_LAYAR;  // Muncul kembali dengan y acak
    }
}

void bikinGambarMusuh(SDL_Renderer* renderer, Musuh* musuh) {
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);  
    SDL_FRect kotakMusuh = {musuh->x, musuh->y, musuh->w, musuh->h};
    SDL_RenderFillRect(renderer, &kotakMusuh);
}