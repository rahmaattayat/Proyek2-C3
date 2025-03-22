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
    int w, h;
    bool nyala;
} PeluruStruct;

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

void bikinPesawat(Pesawat* pesawat);
void bikinPeluru(PeluruStruct* peluru);
void resetKecepatan(Pesawat* pesawat);
void gerakinPesawat(Pesawat* pesawat, const Uint8* keyboard, bool pencetSpasi);
void prosesInput(Pesawat* pesawat, const Uint8* keyboard, bool pencetSpasi);
void kurangiCooldown(Pesawat* pesawat);
void batesinGerakanPesawat(Pesawat* pesawat);
void updatePesawat(Pesawat* pesawat);
void nembak(Pesawat* pesawat);
void jalankanPeluru(Pesawat* pesawat);
void updatePeluru(PeluruStruct* peluru);
void bikinGambarPesawat(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarNOS(SDL_Renderer* renderer, Pesawat* pesawat);
void bikinGambarPeluru(SDL_Renderer* renderer, Pesawat* pesawat);
void tampilNyawa(SDL_Renderer* renderer, Pesawat* pesawat);
void gambarNyawa(SDL_Renderer* renderer, int x, int y, int radius);
void reload(Pesawat* pesawat);
void updateReload(Pesawat* pesawat);
void tampilAmunisi(SDL_Renderer* renderer, Pesawat* pesawat);

#endif //IHSAN_H