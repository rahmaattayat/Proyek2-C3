#ifndef RAHMA_H
#define RAHMA_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "config.h"

#define JUMLAH 5

typedef struct {
    float x, y;       // Posisi musuh
    float dx;           // Kecepatan gerak horizontal & vertikal
    int w, h;         // Ukuran musuh
    int batasAtas, batasBawah; // Batas gerakan vertikal
    int batasKiri, batasKanan; // Batas gerakan horizontal
    int aktif;
} Musuh;

void bikinMusuh(Musuh* musuh, int aktif, int tinggi, int lebar);
void gerakinMusuh(Musuh* musuh);
void bikinGambarMusuh(SDL_Renderer* renderer, Musuh* musuh);

#endif // RAHMA_H