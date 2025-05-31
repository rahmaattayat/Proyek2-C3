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
    int batasAtas, batasBawah; 
    int batasKiri, batasKanan; 
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
void bikinMusuh(Musuh* musuh, int jumlahmusuh, int aktif);
void gerakinMusuh(Musuh* musuh);

int musuhKeluarLayar(Musuh* musuh);
int nabrakPeluru(Pesawat *pesawat, Musuh *musuh);
void nabrakMusuh(SDL_Renderer *renderer, Pesawat *pesawat, Musuh *musuh);
void efekNabrakPeluru(Pesawat *pesawat, Musuh *musuh, int i, int j);
void kelolaGameOver(SDL_Renderer *renderer);

void bikinGambarMusuh(SDL_Renderer* renderer, Musuh* musuh);

#endif // RAHMA_H