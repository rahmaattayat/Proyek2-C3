#ifndef GEMA_H
#define GEMA_H

#include <SDL3/SDL.h>

#define MAKSIMAL_BINTANG 200

// Struktur dan fungsi untuk bintang
typedef struct
{
    float x;
    float y;
    float ukuranBintang;
    float kecepatanBintang;
} Bintang;

Bintang bikinBintang(float x, float y, float size, float speed);

// Struktur dan fungsi untuk background
typedef struct
{
    Bintang bintang[MAKSIMAL_BINTANG]; // Array bintang
    int jumlah;
    int lebarLayar;
    int tinggiLayar;
} Background;

// Inisialisasi background dengan bintang acak
void bikinBackground(Background *background, int lebar, int tinggi);

// Update posisi bintang (bergerak ke kiri)
void updateBackground(Background *background, float selisihWaktu);

// Render bintang-bintang di background
void renderBackground(const Background *background, SDL_Renderer *renderer);

#endif // GEMA_H
