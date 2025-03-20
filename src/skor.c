#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include "alda.h"
#include "fairuz.h"

void tampilskor(SDL_Renderer *renderer, nilai *point)
{
    // Tentukan posisi dan ukuran kotak skor
    SDL_FRect kotakSkor = {0, 0, 300, 20};

    // Tentukan warna untuk kotak dan teks
    SDL_Color warnaKotak = {255, 255, 255, 255}; // putih
    SDL_Color warnaTeks = {0, 0, 0, 255};        // hitam

    // Gambar kotak untuk skor
    SDL_SetRenderDrawColor(renderer, warnaKotak.r, warnaKotak.g, warnaKotak.b, warnaKotak.a);
    SDL_RenderFillRect(renderer, &kotakSkor);

    // Siapkan teks untuk skor dan high skor
    char teksSkor[50];
    char teksHighSkor[50];
    snprintf(teksSkor, sizeof(teksSkor), "Skor: %d", point->skor);
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", point->highskor);

    // Tentukan posisi teks
    float posXSkor = kotakSkor.x + 5; 
    float posYSkor = kotakSkor.y + 5; 
    float posXHighSkor = kotakSkor.x + 125;
    float posYHighSkor = kotakSkor.y + 5; 

    // Gambar teks skor
    SDL_SetRenderDrawColor(renderer, warnaTeks.r, warnaTeks.g, warnaTeks.b, warnaTeks.a);
    SDL_RenderDebugText(renderer, posXSkor, posYSkor, teksSkor);
    SDL_RenderDebugText(renderer, posXHighSkor, posYHighSkor, teksHighSkor);
}

void tambahskor(nilai *point)
{
    point->skor += 10;
}

void kuranginskor (nilai *point)
{
    point->skor -= 10;
}

void cekhighskor(nilai *point)
{
    if (point->skor > point->highskor)
    {
        point->highskor = point->skor;
    }
}

// Fungsi untuk memuat high score dari file
void loadhighskor(nilai *point)
{
    FILE *file = fopen("src/highskor.dat", "r");
    if (file)
    {
        if (fscanf(file, "%d", &point->highskor) != 1)
        {
            printf("Gagal membaca high score dari file!\n");
            point->highskor = 0;
        }
        fclose(file);
    }
    else
    {
        printf("File highskor.dat tidak ditemukan!\n");
        point->highskor = 0;
    }
}

// Fungsi untuk menyimpan high score ke file
void simpanhighskor(nilai *point)
{    
    FILE *file = fopen("src/highskor.dat", "w");
    if (file)
    {
        fprintf(file, "%d", point->highskor);
        fclose(file);
        printf("High score berhasil disimpan!\n");
    }
    else
    {
        printf("Error menyimpan high score");
    }
}

void gameover(SDL_Renderer *renderer, nilai *point)
{
    // // Hentikan layar game
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255); 
    SDL_RenderClear(renderer);

    const char *title = "GAME OVER";
    float titleX = (LEBAR_LAYAR - 200) / 2.0f;
    float titleY = 300;
    teksRender(title, titleX, titleY, 3.0f, (SDL_Color){255, 0, 0, 255}); 

    // // Tentukan warna untuk teks
    SDL_Color warnaSkor = {255, 255, 0, 255}; // kuning

    // Siapkan teks untuk skor, dan high skor
    char teksSkor[50];
    char teksHighSkor[50];
    snprintf(teksSkor, sizeof(teksSkor), "Skor: %d", point->skor);
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", point->highskor);

    float posXSkor = titleX - 140;
    float posYSkor = titleY - 60;
    float posXHighSkor = posXSkor - 20;
    float posYHighSkor = posYSkor + 20; 

    // Gambar teks skor
    SDL_SetRenderDrawColor(renderer, warnaSkor.r, warnaSkor.g, warnaSkor.b, warnaSkor.a);
    SDL_SetRenderScale(renderer, 1.5f, 1.5f);
    SDL_RenderDebugText(renderer, posXSkor, posYSkor, teksSkor);
    SDL_RenderDebugText(renderer, posXHighSkor, posYHighSkor, teksHighSkor);

    // Perbarui layar
    SDL_RenderPresent(renderer);
}