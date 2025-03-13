#ifndef ALDA_H
#define ALDA_H
#include "config.h"
#include <SDL3/SDL.h>
#include "rahma.h"
#include "fairuz.h"

typedef struct
{
    int skor;
    int highskor;
} nilai;

extern nilai nn;

void tambahskor(nilai *nn);
void cekhighskor(nilai *nn);
void tampilskor(SDL_Renderer *renderer, nilai *nn);
#endif // ALDA_H