#ifndef IHSAN_H
#define IHSAN_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "config.h"

//var global
#define MAX_PELURU 50
#define MAX_SUPLAI 2
#define JENIS_SUPLAI 2

typedef struct
{
    float x, y;
    float dx, dy;
    int w, h;
    bool nyala;
} PeluruStruct;

typedef struct
{
    float x, y;
    float dx, dy;
    int w, h;
    bool aktif;
    int jenis;
} Suplai;

typedef struct
{
    float x, y;
    float dx, dy;
    int w, h;//width height(lebar dan tinggi)
    int cd_tembak;//cooldown = cd
    int nyawa;
    int magasin;
    int peluru_sekarang;
    bool sedang_reload;
    int waktu_reload;
    PeluruStruct peluru[MAX_PELURU];
} Pesawat;

extern Suplai suplai[JENIS_SUPLAI][MAX_SUPLAI];

extern Uint32 waktuTerakhirSuplai;
extern Uint32 rentangSpawnSuplai;

void bikinPesawat(Pesawat* pesawat);
void bikinPeluru(PeluruStruct* peluru);
void gerakinPesawat(Pesawat* pesawat, const Uint8* keyboard, bool pencetSpasi);
void updatePesawat(Pesawat* pesawat);
void nembak(Pesawat* pesawat);
void jalankanPeluru(Pesawat* pesawat);
void bikinGambarPesawat(SDL_Renderer* renderer, Pesawat* pesawat);
void bikinGambarPeluru(SDL_Renderer* renderer, Pesawat* pesawat);
void tampilNyawa(SDL_Renderer* renderer, Pesawat* pesawat);
void reload(Pesawat* pesawat);
void updateReload(Pesawat* pesawat);
void tampilAmunisi(SDL_Renderer* renderer, Pesawat* pesawat);
void spawnSuplai(int jenis);
void updateSuplai(SDL_Renderer *renderer, Pesawat* pesawat);
void renderSuplai(SDL_Renderer* renderer);
void loadTeksturSuplai(SDL_Renderer* renderer);
void hapusTeksturSuplai(); 

#endif //IHSAN_H