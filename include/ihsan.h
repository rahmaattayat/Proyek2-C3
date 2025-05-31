#ifndef IHSAN_H
#define IHSAN_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "SDL3_ttf/SDL_ttf.h"

//var global
#define MAX_PELURU 50
#define MAX_SUPLAI 2
#define JENIS_SUPLAI 2
#define CD_TEMBAK 15

typedef struct
{
    float x, y;
    float dx, dy;
    int w, h;
    bool nyala;
} PeluruStruct;

typedef struct PeluruNode
{
    PeluruStruct info;
    struct PeluruNode* prev;
    struct PeluruNode* next;
} PeluruNode;

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
    PeluruNode* peluruHead;
} Pesawat;

extern Suplai suplai[JENIS_SUPLAI][MAX_SUPLAI];
extern Uint32 waktuTerakhirSuplai;
extern Uint32 rentangSpawnSuplai;

extern TTF_Font* font;
void initTTF();
void cleanupTTF();
void renderText(SDL_Renderer* renderer, float x, float y, const char* text, float scale, SDL_Color color);

void bikinPesawat(Pesawat* pesawat);
void bikinPeluru(PeluruStruct* peluru);
PeluruNode *buatPeluruNode();
void tambahPeluruNode(Pesawat* pesawat, PeluruNode* node);
void hapusPeluruNode(Pesawat* pesawat, PeluruNode* node);
void freePeluruList(Pesawat* pesawat);
void gerakinPesawat(Pesawat* pesawat, const Uint8* keyboard, bool pencetSpasi);
void updatePesawat(Pesawat* pesawat);
int nembak(Pesawat* pesawat);
void jalankanPeluru(Pesawat* pesawat);
void bikinGambarPesawat(SDL_Renderer* renderer, Pesawat* pesawat);
void bikinGambarPeluru(SDL_Renderer* renderer, Pesawat* pesawat);
void tampilNyawa(SDL_Renderer* renderer, Pesawat* pesawat);
int reload(Pesawat* pesawat);
void updateReload(Pesawat* pesawat);
void tampilAmunisi(SDL_Renderer* renderer, Pesawat* pesawat);
void inisiasiSuplai(Suplai* suplai, int jenis);
int spawnSuplai(int jenis);
void updatePosisiSuplai(Suplai* suplai);
void cekTabrakanSuplai(Suplai* suplai, Pesawat* pesawat, int jenis);
void updateSuplai(SDL_Renderer* renderer, Pesawat* pesawat);
void renderSuplai(SDL_Renderer* renderer);
void loadTeksturSuplai(SDL_Renderer* renderer);
void hapusTeksturSuplai();
void clearSuplai();

#endif //IHSAN_H