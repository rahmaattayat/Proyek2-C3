#ifndef GEMA_H
#define GEMA_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

// background
#define MAKSIMAL_BINTANG 200

typedef struct
{
    float x;
    float y;
    float ukuranBintang;
    float kecepatanBintang;
} Bintang;

Bintang bikinBintang(float x, float y, float ukuran, float kecepatan);

typedef struct
{
    Bintang bintang[MAKSIMAL_BINTANG]; // Array bintang
    int jumlah;
    int lebarLayar;
    int tinggiLayar;
} Background;

void bikinBackground(Background *background, int lebar, int tinggi);
void updateBackground(Background *background, float selisihWaktu);
void renderBackground(const Background *background, SDL_Renderer *renderer);

// menu
#define LEBAR_TOMBOL 200
#define TINGGI_TOMBOL 50

typedef struct
{
    SDL_FRect kotak;
    const char *teks;
    float skalaTeks;
    bool melayang;
} Tombol;

typedef struct
{
    Tombol tombolPlay;
    Tombol tombolAbout;
} Menu;

void tombolInit(Tombol *tombol, const char *teks, float y, float skalaTeks);
void tombolUpdateHover(Tombol *tombol, float mouseX, float mouseY);
void tombolRender(Tombol *tombol);
bool tombolDiklik(Tombol *tombol, float mouseX, float mouseY);
void teksRender(const char *teks, float x, float y, float skala, SDL_Color warna);
void menuInit(Menu *menu);
void menuUpdate(Menu *menu, float mouseX, float mouseY);
void menuRender(Menu *menu, const Background *background);
void aboutRender();
void aboutInput(SDL_Event *e, bool *tampilAbout);

// status game
typedef enum
{
    STATE_MENU,
    STATE_GAME,
    STATE_ABOUT
} statusGame;

#endif // GEMA_H
