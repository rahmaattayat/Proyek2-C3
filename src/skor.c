#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include "alda.h"
#include "fairuz.h"
//fungsi untuk menampilkan skor dan highskor di layar saat game berjalan
void tampilskor(SDL_Renderer *renderer)
{
    addressuser user = findUser(currentUsername);
    if (!user)
    {
        printf("User tidak ditemukan jadi skor tidak ditampilkan\n");
        return;
    }

    // Tentukan posisi kotak skor
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
    snprintf(teksSkor, sizeof(teksSkor), "Skor: %d", user->score);
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", user->hskor);

    // Tentukan posisi teks
    float posXSkor = kotakSkor.x + 5;
    float posYSkor = kotakSkor.y - 1;
    float posXHighSkor = kotakSkor.x + 125;
    float posYHighSkor = kotakSkor.y - 1;

    // Gambar teks skor
    renderText(renderer, posXSkor, posYSkor, teksSkor, 0.8f, warnaTeks);
    renderText(renderer, posXHighSkor, posYHighSkor, teksHighSkor, 0.8f, warnaTeks);
}
// Fungsi untuk menambahkan skor ketika musuh besar dikalahkan
int tambahskormusuhbesar (int skor)
{
    return skor + 30 * bonus;
}
// Fungsi untuk menambahkan skor ketika musuh kecil dikalahkan
int tambahskor (int skor)
{
    return skor + 10 * bonus;
}
// Fungsi untuk mengurangi skor ketika musuh kecil keluar layar
int kuranginskor(int skor)
{
    return skor - 10;
}
// Fungsi untuk mengurangi skor ketika musuh besar keluar layar
int kuranginskormusuhbesar(int skor)
{
    return skor - 30;
}
// Fungsi untuk mengecek dan memperbarui high skor
void cekhighskor(addressuser user)
{
    if (!user) return;
    if (user->score > user->hskor)
    {
        user->hskor = user->score;
    }
}
// Fungsi untuk tampilkan game over
void gameover(SDL_Renderer *renderer, addressuser user)
{
    // // hentikan layar game
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255);
    SDL_RenderClear(renderer);

    const char *title = "GAME OVER";
    float titleX = (LEBAR_LAYAR - 380) / 2.0f;
    float titleY = 250;
    renderText(renderer, titleX, titleY, title, 3.0f, (SDL_Color){255, 0, 0, 255});

    // // Tentukan warna untuk teks
    SDL_Color warnaSkor = {255, 255, 0, 255}; // kuning

    // Siapkan teks untuk skor, dan high skor
    char teksSkor[50];
    char teksHighSkor[50];
    snprintf(teksSkor, sizeof(teksSkor), "Skor: %d", user->score);
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", user->hskor);

    float posXSkor = (LEBAR_LAYAR - 140) / 2.0f;
    float posYSkor = titleY + 90;
    float posXHighSkor = (LEBAR_LAYAR - 235) / 2.0f;
    float posYHighSkor = posYSkor + 40;

    // Gambar teks skor
    renderText(renderer, posXSkor, posYSkor, teksSkor, 1.5f, warnaSkor);
    renderText(renderer, posXHighSkor, posYHighSkor, teksHighSkor, 1.5f, warnaSkor);

    // Perbarui layar
    SDL_RenderPresent(renderer);
}