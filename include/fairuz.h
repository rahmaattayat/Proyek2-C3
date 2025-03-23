#ifndef FAIRUZ_H
#define FAIRUZ_H

#include "rahma.h"
#include "alda.h"
#include "gema.h"
#include "ihsan.h"
#include "config.h"
#include <SDL3/SDL.h>

#define MAX_MUSUH 10000
#define MAX_WAVE 1000

extern int waveterbaru;
extern int jumlahmusuh;
extern int bonus;

void updatewave(Musuh *musuh);
void cekmusuh(Musuh *musuh);
void kuranginskor(nilai *point);
void tambahmusuh(Musuh *musuh);
void tampilkanWave(SDL_Renderer *renderer);
void kuranginskormusuhbesar(nilai *point);
void bonuswave(int waveterbaru);

#endif
