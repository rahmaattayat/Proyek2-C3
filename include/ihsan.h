#ifndef IHSAN_H
#define IHSAN_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "config.h"

//var global
#define MAX_PELURU 50

typedef struct
{
    float x, y;
    float dx, dy;
    bool nyala;
} PeluruStruct;

typedef struct
{
    float x, y;
    float dx, dy;
    int w, h;//width height(lebar dan tinggi)
    int cd_tembak;//cooldown = cd
    int nyawa;
    PeluruStruct peluru[MAX_PELURU];
} Pesawat;

void bikinPesawat(Pesawat* pesawat);
void bikinPeluru(PeluruStruct* peluru);
void resetKecepatan(Pesawat* pesawat);
void gerakinPesawat(Pesawat* pesawat, const Uint8* keyboard, bool pencetSpasi);
void prosesInputGerak(Pesawat* pesawat, const Uint8* keyboard);
void prosesInputTembak(Pesawat* pesawat, bool pencetSpasi);
void kurangiCooldown(Pesawat* pesawat);
void penggerakPesawat(Pesawat* pesawat);
void batesiGerakanPesawat(Pesawat* pesawat);
void updatePesawat(Pesawat* pesawat);
void nembak(Pesawat* pesawat);
void jalankanPeluru(Pesawat* pesawat);
void updatePosisiPeluru(PeluruStruct* peluru);
void cekPeluruKeluarLayar(PeluruStruct* peluru);
void bikinGambarPesawat(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarBadanPesawat(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarSayap(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarKokpit(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarMoncongan(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarNOS(SDL_Renderer* renderer, Pesawat* pesawat);
void bikinGambarPeluru(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarBadanPeluru(SDL_Renderer* renderer, PeluruStruct* peluru);
void gambarTrailPeluru(SDL_Renderer* renderer, PeluruStruct* peluru);
void tampilNyawa(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarTeksNyawa(SDL_Renderer* renderer);
void gambarIkonNyawa(SDL_Renderer* renderer, int x, int y, int radius);

#endif //IHSAN_H