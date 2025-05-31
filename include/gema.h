#ifndef GEMA_H
#define GEMA_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "alda.h"

// background
#define MAX_BINTANG 200

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
    Bintang bintang[MAX_BINTANG];
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
    bool hover;
} Tombol;

typedef struct
{
    Tombol tombolPlay;
    Tombol tombolAbout;
    Tombol tombolTutorial;
    Tombol tombolLeaderboard;
    Tombol tombolExit;
} Menu;

void tombolInit(Tombol *tombol, const char *teks, float y, int skalaTeks);
bool TombolHover(const Tombol *tombol, float mouseX, float mouseY);
void tombolUpdateHover(Tombol *tombol, float mouseX, float mouseY);
void renderTombol(Tombol *tombol);

void renderIsiMenu(const char **teks, int jumlahBaris, int startX, int startY, int jarakY);

void menuInit(Menu *menu);
void updateSemuaTombol(Menu *menu, float mouseX, float mouseY);
void renderTombolMenu(Menu *menu);
void renderMenu(Menu *menu, const Background *background);

void renderAbout();
void renderTutorial();

// Tampilan LeaderBoard

void renderLeaderboard(SDL_Renderer *renderer, const Background *background);

// ttf tambahan untuk posisi sumbu x teks

void getTextSize(const char* text, float scale, int* width, int* height);
#endif // GEMA_H
