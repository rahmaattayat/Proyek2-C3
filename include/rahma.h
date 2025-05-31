#ifndef RAHMA_H
#define RAHMA_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "ihsan.h"
#include "gema.h"

#define JENIS_MUSUH 2  // 0: musuh biasa, 1: musuh kuat

typedef struct {
    float x, y;       
    float dx;         
    int w, h;         
    int batasKiri;
    int aktif;
    int hp;
    int tipe;
} Musuh;

typedef struct NodeMusuh {
    Musuh data;
    struct NodeMusuh* prev;
    struct NodeMusuh* next;
} NodeMusuh;

extern int musuhAtribut[JENIS_MUSUH][3]; // [tipe][atribut] -> hp, width, height
extern NodeMusuh* headMusuh;

void tambahNodeMusuh(Musuh musuh);
void hapusNodeMusuh(NodeMusuh* node);
void freeMusuh();

void aturAtributMusuh(Musuh* musuh);
void bikinMusuh(int jumlahmusuh);
void gerakinMusuh();

int musuhKeluarLayar();
int nabrakPeluru(Pesawat* pesawat);
void nabrakMusuh(SDL_Renderer* renderer, Pesawat *pesawat);
void efekNabrakPeluru(Pesawat* pesawat, Musuh *musuh);
void kelolaGameOver(SDL_Renderer* renderer);

void bikinGambarMusuh(SDL_Renderer* renderer);

#endif // RAHMA_H