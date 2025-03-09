#ifndef RAHMA_H
#define RAHMA_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "ihsan.h"

#define JUMLAH 5

typedef struct {
    float x, y;       
    float dx;         
    int w, h;         
    int batasAtas, batasBawah; 
    int batasKiri, batasKanan; 
    int aktif;
} Musuh;

void bikinMusuh(Musuh* musuh, int aktif, int tinggi, int lebar);
void gerakinMusuh(Musuh* musuh);
void nabrakPeluru(Pesawat *pesawat, Musuh musuh[]);
void bikinGambarMusuh(SDL_Renderer* renderer, Musuh* musuh);

#endif // RAHMA_H