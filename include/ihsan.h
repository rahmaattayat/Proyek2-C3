#ifndef IHSAN_H
#define IHSAN_H

#include <SDL3/SDL.h>
#include <stdbool.h>

//var global
#define MAX_PELURU 50
#define LEBAR 0
#define TINGGI 1

typedef struct {
    float x, y;
    float dx, dy;
    bool nyala;
} PeluruStruct;

typedef struct {
    float x, y;
    float dx, dy;
    int w, h;//width height(lebar dan tinggi)
    int cd_tembak;//cooldown = cd
    PeluruStruct peluru[MAX_PELURU];
} Pesawat;

extern int layar[2];//layar[LEBAR], layar[TINGGI]

void bikinPesawat(Pesawat* pesawat);
void gerakinPesawat(Pesawat* pesawat, const Uint8* keyboard, bool pencetSpasi);
void updatePesawat(Pesawat* pesawat);
void bikinGambarPesawat(SDL_Renderer* renderer, Pesawat* pesawat);
void nembak(Pesawat* pesawat);
void jalankanPeluru(Pesawat* pesawat);
void bikinGambarPeluru(SDL_Renderer* renderer, Pesawat* pesawat);
#endif //IHSAN_H