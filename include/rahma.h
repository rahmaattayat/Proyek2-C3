#ifndef RAHMA_H
#define RAHMA_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
    float x, y;       // Posisi musuh
    float dx, dy;     // Kecepatan gerak horizontal & vertikal
    int w, h;         // Ukuran musuh
    int batasAtas, batasBawah; // Batas gerakan vertikal
    int batasKiri, batasKanan; // Batas gerakan horizontal
} Musuh;

void bikinMusuh(Musuh* musuh, int layarLebar, int layarTinggi);
void gerakinMusuh(Musuh* musuh);
void bikinGambarMusuh(SDL_Renderer* renderer, Musuh* musuh);

#endif // RAHMA_H