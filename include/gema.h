#ifndef GEMA_H
#define GEMA_H

#include <SDL3/SDL.h>

#define MAX_STARS 200

// Struktur dan fungsi untuk bintang
typedef struct {
    float x;
    float y;
    float size;
    float speed;
} Star;

Star bikinBintang(float x, float y, float size, float speed);

// Struktur dan fungsi untuk background
typedef struct {
    Star stars[MAX_STARS]; // Array bintang
    int count;
    int screenWidth;
    int screenHeight;
} Background;

// Inisialisasi background dengan bintang acak
void bikinBackground(Background* bg, int width, int height);

// Update posisi bintang (bergerak ke kiri)
void updateBackground(Background* bg, float deltaTime);

// Render bintang-bintang di background
void renderBackground(const Background* bg, SDL_Renderer* renderer);

#endif // GEMA_H
