#ifndef GEMA_H
#define GEMA_H

#include <SDL3/SDL.h>

#define MAX_STARS 200

// Struktur dan fungsi untuk bintang
typedef struct {
    float x;
    float y;
    float size;
} Star;

Star create_star(float x, float y, float size);

// Struktur dan fungsi untuk background
typedef struct {
    Star stars[MAX_STARS]; // Array bintang
    int count;
    int screenWidth;
    int screenHeight;
} Background;

// Inisialisasi background dengan bintang acak
void inisialisasi_background(Background* bg, int width, int height);

// Update posisi bintang (bergerak ke kiri)
void update_background(Background* bg, float deltaTime);

// Render bintang-bintang di background
void render_background(const Background* bg, SDL_Renderer* renderer);

#endif // GEMA_H
