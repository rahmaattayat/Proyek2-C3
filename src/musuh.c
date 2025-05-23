#include "Rahma.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include "fairuz.h"
#include "alda.h"
#include "gema.h"

int jumlahmusuh = 5;
extern statusGame state;

int musuhAtribut[JENIS_MUSUH][3] =
    {
        {1, 65, 65}, // musuh biasa: hp, width, height
        {3, 85, 85}  // musuh kuat: hp, width, height
};

void inisialisasiMusuh(Musuh *musuh, int jumlahmusuh)
{
    int jarak_musuh = 100; 
    int jarak_vertikal = 80; 

    for (int i = 0; i < jumlahmusuh; i++)
    {
        musuh[i].x = LEBAR_LAYAR + i * jarak_musuh;
        musuh[i].y = 10 + (i % 5) * jarak_vertikal; 
        musuh[i].dx = -(2 + rand() % 2); 
        musuh[i].batasKiri = -10;
        musuh[i].aktif = 1;
    }
}

void aturAtributMusuh(Musuh *musuh)
{
    musuh->hp = musuhAtribut[musuh->tipe][0];
    musuh->w = musuhAtribut[musuh->tipe][1];
    musuh->h = musuhAtribut[musuh->tipe][2];
    musuh->y = 10 + rand() % (TINGGI_LAYAR - musuh->h - 20);
}

void tipeMusuh(Musuh *musuh, int jumlahmusuh, int jumlahMusuhKuat)
{
    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (jumlahMusuhKuat > 0 && (rand() % 100 < 50))
        {
            musuh[i].tipe = 1; // musuh kuat
            jumlahMusuhKuat--;
        }
        else
        {
            musuh[i].tipe = 0; // musuh biasa
        }
        aturAtributMusuh(&musuh[i]);
    }
}

void bikinMusuh(Musuh *musuh, int jumlahmusuh, int aktif)
{
    // nentuin musuh berdasarkan wave
    int jumlahMusuhKuat = 0;
    if (waveterbaru >= 5)
    {
        jumlahMusuhKuat = waveterbaru - 4; // musuh kuat bertambah kalo wave bertambah
        if (jumlahMusuhKuat > jumlahmusuh / 3)
        {
            jumlahMusuhKuat = jumlahmusuh / 3;
        }
    }
    inisialisasiMusuh(musuh, jumlahmusuh);
    tipeMusuh(musuh, jumlahmusuh, jumlahMusuhKuat);
}

void gerakinMusuh(Musuh *musuh)
{
    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].aktif)
        {
            musuh[i].x += musuh[i].dx; // gerak musuh yg kecepatan dx
        }
    }
}

int musuhKeluarLayar(Musuh *musuh)
{
    int countReset = 0;
    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].x + musuh[i].w < 0)
        {
            if (musuh[i].tipe == 1)
            {
                point.skor = kuranginskormusuhbesar(point.skor);
            }
            else
            {
                point.skor = kuranginskor(point.skor);
            }
            musuh[i].x = LEBAR_LAYAR + 10;
            musuh[i].y = 10 + rand() % (TINGGI_LAYAR - musuh[i].h - 20);
            countReset++;
        }
    }
    return countReset;
}

int nabrakPeluru(Pesawat *pesawat, Musuh *musuh)
{
    int hitCount = 0;
    PeluruNode* current = pesawat->peluruHead;
    while (current)
    {
        PeluruNode* next = current->next;
        if (current->info.nyala)
        {
            for (int j = 0; j < jumlahmusuh; j++)
            {
                if (!musuh[j].aktif)
                    continue;

                if (current->info.x < musuh[j].x + musuh[j].w &&
                    current->info.x + current->info.w > musuh[j].x &&
                    current->info.y < musuh[j].y + musuh[j].h &&
                    current->info.y + current->info.h > musuh[j].y)
                {
                    // Simulasi indeks i untuk kompatibilitas
                    efekNabrakPeluru(pesawat, musuh, 0, j); // Indeks i tidak digunakan
                    hapusPeluruNode(pesawat, current);
                    hitCount++;
                    break;
                }
            }
        }
        current = next;
    }
    return hitCount;
}

void efekNabrakPeluru(Pesawat *pesawat, Musuh *musuh, int i, int j)
{
    // kurangi hp musuh
    musuh[j].hp--;
    // matiin musuh yg hp nya habis
    if (musuh[j].hp <= 0)
    {
        musuh[j].aktif = 0;
        playEnemyDeathSound();
        // tambah skor berdasarkan tipe musuh
        if (musuh[j].tipe == 1)
        {
            point.skor = tambahskormusuhbesar(point.skor);
        }
        else
        {
            point.skor = tambahskor(point.skor);
        }
        cekhighskor(&point);
    }
}

void nabrakMusuh(SDL_Renderer *renderer, Pesawat *pesawat, Musuh *musuh)
{
    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].aktif && pesawat->x < musuh[i].x + musuh[i].w && pesawat->x + pesawat->w > musuh[i].x &&
            pesawat->y < musuh[i].y + musuh[i].h && pesawat->y + pesawat->h > musuh[i].y)
        {
            if (musuh[i].tipe == 1)
            {
                pesawat->nyawa = pesawat->nyawa - 2;
            }
            else
            {
                pesawat->nyawa = pesawat->nyawa - 1;
            }
            playPlayerHitSound();
            musuh[i].aktif = 0;

            if (pesawat->nyawa <= 0)
            {
                kelolaGameOver(renderer);
                return;
            }
        }
    }
}

void kelolaGameOver(SDL_Renderer *renderer)
{
    playMusic(gameOverMusic);
    gameover(renderer, &point);
    simpanhighskor(&point);

    // reset skor untuk game berikutnya
    point.skor = 0;
    // tunda 2 detik
    SDL_Delay(4000);
    // ubah state ke menu
    state = STATE_MENU;
    playMusic(menuMusic);
    // reset jumlah musuh dan wave untuk game berikutnya
    jumlahmusuh = 5;
    waveterbaru = 1;
}

void bikinGambarMusuh(SDL_Renderer *renderer, Musuh *musuh)
{
    // warna buat musuh biasa
    SDL_Color warnaTubuh = {50, 255, 70, 255};   // hijau
    SDL_Color warnaMata = {255, 50, 50, 255};    // merah
    SDL_Color warnaDetail = {200, 200, 20, 255}; // kuning

    // warna buat musuh kuat
    SDL_Color warnaTubuhKuat = {150, 50, 200, 255}; // ungu
    SDL_Color warnaMataKuat = {255, 200, 0, 255};   // orange
    SDL_Color warnaDetailKuat = {0, 200, 255, 255}; // cyan

    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].aktif)
        {
            float x = musuh[i].x;
            float y = musuh[i].y;
            float w = musuh[i].w;
            float h = musuh[i].h;

            float TengahanX = x + w / 2;
            float TengahanY = y + h / 2;

            // warna berdasarkan tipe musuh
            SDL_Color currentTubuh, currentMata, currentDetail;
            if (musuh[i].tipe == 1)
            { // musuh kuat
                currentTubuh = warnaTubuhKuat;
                currentMata = warnaMataKuat;
                currentDetail = warnaDetailKuat;
            }
            else
            { // musuh biasa
                currentTubuh = warnaTubuh;
                currentMata = warnaMata;
                currentDetail = warnaDetail;
            }

            // kepala
            SDL_FRect kepala = {TengahanX - w * 0.4f, y + h * 0.1f, w * 0.8f, h * 0.5f};
            SDL_SetRenderDrawColor(renderer, currentTubuh.r, currentTubuh.g, currentTubuh.b, currentTubuh.a);
            SDL_RenderFillRect(renderer, &kepala);

            // mata
            SDL_SetRenderDrawColor(renderer, currentMata.r, currentMata.g, currentMata.b, currentMata.a);
            SDL_FRect mataKiri = {TengahanX - w * 0.25f, y + h * 0.2f, w * 0.15f, h * 0.15f};
            SDL_FRect mataKanan = {TengahanX + w * 0.10f, y + h * 0.2f, w * 0.15f, h * 0.15f};
            SDL_RenderFillRect(renderer, &mataKiri);
            SDL_RenderFillRect(renderer, &mataKanan);

            // antenna
            SDL_SetRenderDrawColor(renderer, currentDetail.r, currentDetail.g, currentDetail.b, currentDetail.a);
            SDL_RenderLine(renderer, TengahanX - w * 0.25f, y + h * 0.1f, TengahanX - w * 0.4f, y);
            SDL_RenderLine(renderer, TengahanX + w * 0.25f, y + h * 0.1f, TengahanX + w * 0.4f, y);

            // indikator hp musuh kuat
            if (musuh[i].tipe == 1)
            {
                // hp bar
                float hpBarWidth = w * 0.8f;
                float hpBarHeight = h * 0.05f;
                float hpBarX = TengahanX - hpBarWidth / 2;
                float hpBarY = y - hpBarHeight - 5;

                SDL_FRect hpBarBg = {hpBarX, hpBarY, hpBarWidth, hpBarHeight};
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 200);
                SDL_RenderFillRect(renderer, &hpBarBg);

                // isi hp bar berdasarkan sisa hp
                float hpFill = (float)musuh[i].hp / 3.0f * hpBarWidth;
                SDL_FRect hpBarFill = {hpBarX, hpBarY, hpFill, hpBarHeight};
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &hpBarFill);
            }

            // tangan
            SDL_SetRenderDrawColor(renderer, currentDetail.r, currentDetail.g, currentDetail.b, currentDetail.a);
            SDL_FRect tanganKiri = {x, y + h * 0.3f, w * 0.1f, h * 0.2f};
            SDL_FRect tanganKanan = {x + w * 0.9f, y + h * 0.3f, w * 0.1f, h * 0.2f};
            SDL_RenderFillRect(renderer, &tanganKiri);
            SDL_RenderFillRect(renderer, &tanganKanan);

            // tentakel
            SDL_FRect tentakel1 = {TengahanX - w * 0.25f, y + h * 0.6f, w * 0.1f, h * 0.2f};
            SDL_FRect tentakel2 = {TengahanX - w * 0.05f, y + h * 0.6f, w * 0.1f, h * 0.2f};
            SDL_FRect tentakel3 = {TengahanX + w * 0.15f, y + h * 0.6f, w * 0.1f, h * 0.2f};
            SDL_RenderFillRect(renderer, &tentakel1);
            SDL_RenderFillRect(renderer, &tentakel2);
            SDL_RenderFillRect(renderer, &tentakel3);

            // mulut
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_FRect mouth = {TengahanX - w * 0.15f, y + h * 0.45f, w * 0.3f, h * 0.05f};
            SDL_RenderFillRect(renderer, &mouth);

            // alis
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderLine(renderer, TengahanX - w * 0.3f, y + h * 0.17f, TengahanX - w * 0.1f, y + h * 0.23f);
            SDL_RenderLine(renderer, TengahanX + w * 0.1f, y + h * 0.23f, TengahanX + w * 0.3f, y + h * 0.18f);
        }
    }
}