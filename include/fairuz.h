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

typedef struct Node
{
    int waveNumber;    // Menyimpan nomor wave
    struct Node *next; // Pointer ke node berikutnya
} Node;

void addWave(Node **head, int waveNumber);
void freeWaves(Node *head);

// Fungsi lainnya
void updatewave(Musuh *musuh);
void cekmusuh(Musuh *musuh);
int kuranginskor(int skor);
int tambahmusuh(int jumlahmusuh, int waveterbaru);
void tampilkanWave(SDL_Renderer *renderer);
int kuranginskormusuhbesar(int skor);
void bonuswave(int waveterbaru);

#endif
