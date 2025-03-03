#include "gema.h"
#include <stdlib.h>

void inisialisasi_background(Background* bg, int width, int height) {
    bg->count = MAX_STARS;
    bg->screenWidth = width;
    bg->screenHeight = height;

    for (int i = 0; i < MAX_STARS; i++) {
        float x = (float)(rand() % width);
        float y = (float)(rand() % height);
        float size = 1.0f + (rand() % 3);
        float speed = 0.5f + (rand() % 3);  // Kecepatan antara 0.5 hingga 3.0
        bg->stars[i] = create_star(x, y, size, speed);
    }
}

void update_background(Background* bg, float deltaTime) {
    for (int i = 0; i < bg->count; i++) {
        bg->stars[i].x -= bg->stars[i].speed * deltaTime;  // Gunakan kecepatan unik

        // Jika keluar layar, pindahkan ke kanan
        if (bg->stars[i].x < 0) {
            bg->stars[i].x = bg->screenWidth;
            bg->stars[i].y = rand() % bg->screenHeight; // Random posisi Y baru
            bg->stars[i].speed = 0.5f + (rand() % 3);  // Beri kecepatan baru
        }
    }
}


void render_background(const Background* bg, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // warna putih
    for (int i = 0; i < bg->count; i++) {
        SDL_FRect starRect = { bg->stars[i].x, bg->stars[i].y, bg->stars[i].size, bg->stars[i].size };
        SDL_RenderFillRect(renderer, &starRect);
    }
}
