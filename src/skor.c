#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include "alda.h"

void tampilskor(SDL_Renderer *renderer, nilai *point)
{
    // Tentukan posisi dan ukuran kotak skor
    SDL_FRect kotakSkor = { 0, 0, 300, 20 };

    // Tentukan warna untuk kotak dan teks
    SDL_Color warnaKotak = { 255, 255, 255, 255 }; // putih
    SDL_Color warnaTeks = { 0, 0, 0, 255  }; // hitam

    // Gambar kotak untuk skor
    SDL_SetRenderDrawColor(renderer, warnaKotak.r, warnaKotak.g, warnaKotak.b, warnaKotak.a);
    SDL_RenderFillRect(renderer, &kotakSkor);

    // Siapkan teks untuk skor dan high skor
    char teksSkor[50];
    char teksHighSkor[50];
    snprintf(teksSkor, sizeof(teksSkor), "Skor: %d", point->skor);
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", point->highskor);

    // Tentukan posisi teks
    float posXSkor = kotakSkor.x + 5; // Menggeser teks sedikit ke kiri
    float posYSkor = kotakSkor.y + 5; // Menggeser teks sedikit ke bawah
    float posXHighSkor = kotakSkor.x + 125; // Menambahkan jarak antara teks skor dan high skor
    float posYHighSkor = kotakSkor.y + 5; // Menggeser teks sedikit ke bawah

    // Gambar teks skor
    SDL_SetRenderDrawColor(renderer, warnaTeks.r, warnaTeks.g, warnaTeks.b, warnaTeks.a);
    SDL_RenderDebugText(renderer, posXSkor, posYSkor, teksSkor);
    SDL_RenderDebugText(renderer, posXHighSkor, posYHighSkor, teksHighSkor);
}

void tambahskor(nilai *point)
{
    point->skor += 10;
}

void cekhighskor(nilai *point)
{
    if (point->skor > point->highskor)
    {
        point->highskor = point->skor;
    }
}