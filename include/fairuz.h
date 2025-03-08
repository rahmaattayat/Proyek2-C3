#ifndef FAIRUZ_H
#define FAIRUZ_H

#include "rahma.h"
#include "alda.h"
#include "gema.h"
#include "ihsan.h"
#include "config.h"

#define MAX_MUSUH 50

typedef struct {
    Musuh musuhAsli;
    int aktif;        
} MusuhGameplay;

void inisialisasiMusuh(int layarLebar, int layarTinggi);
void cekWaveBaru(int layarLebar, int layarTinggi);
void updateMusuh();
void gambarMusuh(SDL_Renderer* renderer);

#endif

