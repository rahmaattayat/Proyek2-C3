#ifndef ALDA_H
#define ALDA_H
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include "config.h"
#include "gema.h"

typedef struct
{
    int skor;
    int highskor;
} nilai;

extern nilai point;

void tampilskor(SDL_Renderer *renderer, nilai *point);
void tambahskor(nilai *point);
void cekhighskor(nilai *point);
void loadhighskor(nilai *point);
void simpanhighskor(nilai *point);
void gameover(SDL_Renderer *renderer, nilai *point);

#endif // ALDA_H