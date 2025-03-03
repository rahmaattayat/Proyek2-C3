#include "Rahma.h"
#include <SDL3/SDL.h>

void bikinMusuh(Musuh* musuh, int layarLebar, int layarTinggi) {
    musuh->x = layarLebar - 100;  
    musuh->y = layarTinggi / 3;   
    musuh->w = 50;
    musuh->h = 40;
    musuh->dx = -2.5f;            // Kecepatan maju musuh ke kiri
    // musuh->dy = 2.0f;          // Kecepatan gerak vertikal
    musuh->batasAtas = 50;
    musuh->batasBawah = layarTinggi - 50;
    musuh->batasKiri = -50;       
}

void gerakinMusuh(Musuh* musuh) {
    // Gerak horizontal (maju ke kiri)
    musuh->x += musuh->dx;

    // Jika musuh melewati batas kiri layar, reset ke posisi awal 
    // if (musuh->x + musuh->w < musuh->batasKiri) {
    //     musuh->x = 800;  
    // }

    // Gerak vertikal
    // musuh->y += musuh->dy;

    // Jika menyentuh batas, balik arah gerakan vertikal
    if (musuh->y <= musuh->batasAtas || musuh->y + musuh->h >= musuh->batasBawah) {
        musuh->dy = -musuh->dy;
    }
}

void bikinGambarMusuh(SDL_Renderer* renderer, Musuh* musuh) {
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);  
    SDL_FRect kotakMusuh = {musuh->x, musuh->y, musuh->w, musuh->h};
    SDL_RenderFillRect(renderer, &kotakMusuh);
}