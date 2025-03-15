#ifndef ALDA_H
#define ALDA_H
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>

typedef struct
{
    int skor;
    int highskor;
} nilai;

extern nilai point;

void tampilskor(SDL_Renderer *renderer, nilai *point);
void tambahskor(nilai *point);
void cekhighskor(nilai *point);

#endif // ALDA_H