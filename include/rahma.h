#ifndef RAHMA_H
#define RAHMA_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "ihsan.h"
#include "gema.h"

#define JENIS_MUSUH 2  // 0: musuh biasa, 1: musuh kuat
extern int musuhAtribut[JENIS_MUSUH][3]; // [tipe][atribut] -> hp, width, height

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

void bikinMusuh(Musuh* musuh, int jumlahmusuh, int aktif, int tinggi, int lebar);
void gerakinMusuh(Musuh* musuh);
void nabrakPeluru(Pesawat *pesawat, Musuh *musuh);
void bikinGambarMusuh(SDL_Renderer* renderer, Musuh* musuh);
void nabrakMusuh(SDL_Renderer *renderer, Pesawat *pesawat, Musuh *musuh);

#endif // RAHMA_H