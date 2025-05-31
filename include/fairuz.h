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
typedef struct Node Node;  // bilang ke compiler bahwa Node itu tipe struct yang akan didefinisikan nanti


extern int jumlahmusuh;
extern int bonus;
extern Node *headWave; // Linked list wave harus dideklarasikan di file lain, misal fairuz.c


typedef struct Node
{
    int waveNumber;    // Menyimpan nomor wave
    struct Node *next; // Pointer ke node berikutnya
} Node;

void addWave(Node **head, int waveNumber);
void freeWaves(Node *head);
int getLastWaveNumber(Node *head);


// Fungsi lainnya
void updatewave();
void cekmusuh();
int kuranginskor(int skor);
int tambahmusuh(int jumlahmusuh, int waveterbaru);
void tampilkanWave(SDL_Renderer *renderer);
int kuranginskormusuhbesar(int skor);
void bonuswave(int waveterbaru);

#endif
