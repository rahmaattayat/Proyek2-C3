#include "Rahma.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include "fairuz.h"
#include "alda.h"
#include "gema.h"

int jumlahmusuh = 5;
extern statusGame state;
NodeMusuh *headMusuh = NULL;

int musuhAtribut[JENIS_MUSUH][3] =
    {
        {1, 65, 65}, // musuh biasa: hp, width, height
        {3, 85, 85}  // musuh kuat: hp, width, height
};

void aturAtributMusuh(Musuh *musuh)
{
    musuh->hp = musuhAtribut[musuh->tipe][0];
    musuh->w = musuhAtribut[musuh->tipe][1];
    musuh->h = musuhAtribut[musuh->tipe][2];
    musuh->y = 10 + rand() % (TINGGI_LAYAR - musuh->h - 20);
}

Musuh buatMusuh(int index, int *jumlahMusuhKuat)
{
    Musuh musuh;
    musuh.x = LEBAR_LAYAR + index * 100;
    musuh.y = 10 + (index % 5) * 80;
    musuh.dx = -(2 + rand() % 2);
    musuh.batasKiri = -10;
    musuh.aktif = 1;

    if (*jumlahMusuhKuat > 0 && rand() % 100 < 50)
    {
        musuh.tipe = 1;
        (*jumlahMusuhKuat)--;
    }
    else
    {
        musuh.tipe = 0;
    }

    aturAtributMusuh(&musuh);
    return musuh;
}

void bikinMusuh(Musuh *musuh, int jumlah, int aktif)
{
    freeMusuh();
    headMusuh = NULL;

    int jumlahMusuhKuat;
    int currentWave = getLastWaveNumber(headWave);  // <== Panggil fungsi dengan parameter head wave

    if (currentWave >= 5)
    {
        jumlahMusuhKuat = currentWave - 4;
    }
    else
    {
        jumlahMusuhKuat = 0;
    }

    if (jumlahMusuhKuat > jumlah / 3)
        jumlahMusuhKuat = jumlah / 3;

    for (int i = 0; i < jumlah; i++)
    {
        Musuh musuh = buatMusuh(i, &jumlahMusuhKuat);
        tambahNodeMusuh(musuh);
    }
}

void tambahNodeMusuh(Musuh musuh)
{
    NodeMusuh *newNode = (NodeMusuh *)malloc(sizeof(NodeMusuh));
    newNode->data = musuh;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (headMusuh == NULL)
    {
        headMusuh = newNode;
    }
    else
    {
        NodeMusuh *temp = headMusuh;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void hapusNodeMusuh(NodeMusuh *node)
{
    if (!node)
        return;

    if (node->prev)
        node->prev->next = node->next;
    else
        headMusuh = node->next;

    if (node->next)
        node->next->prev = node->prev;

    free(node);
}

void freeMusuh()
{
    NodeMusuh *current = headMusuh;
    while (current)
    {
        NodeMusuh *temp = current;
        current = current->next;
        free(temp);
    }
    headMusuh = NULL;
}

void gerakinMusuh(Musuh *musuh)
{
    NodeMusuh *curr = headMusuh;
    while (curr)
    {
        if (curr->data.aktif)
            curr->data.x += curr->data.dx;
        curr = curr->next;
    }
}

int musuhKeluarLayar(Musuh *musuh)
{
    addressuser user = findUser(currentUsername);
    int countReset = 0;
    NodeMusuh *curr = headMusuh;
    while (curr)
    {
        if (curr->data.x + curr->data.w < 0)
        {
            if (curr->data.tipe == 1)
            {
                user->score = kuranginskormusuhbesar(user->score);
            }
            else
            {
                user->score = kuranginskor(user->score);
            }

            curr->data.x = LEBAR_LAYAR + 10;
            curr->data.y = 10 + rand() % (TINGGI_LAYAR - curr->data.h - 20);
            countReset++;
        }
        curr = curr->next;
    }
    return countReset;
}

int nabrakPeluru(Pesawat *pesawat, Musuh *musuh)
{
    int hitCount = 0;
    PeluruNode *current = pesawat->peluruHead;
    while (current)
    {
        PeluruNode *next = current->next;
        if (current->info.nyala)
        {
            NodeMusuh *musuhNode = headMusuh;
            while (musuhNode)
            {
                Musuh *musuh = &musuhNode->data;
                if (!musuh->aktif)
                {
                    musuhNode = musuhNode->next;
                    continue;
                }

                if (current->info.x < musuh->x + musuh->w &&
                    current->info.x + current->info.w > musuh->x &&
                    current->info.y < musuh->y + musuh->h &&
                    current->info.y + current->info.h > musuh->y)
                {
                    efekNabrakPeluru(pesawat, musuh, 0, 0);
                    hapusPeluruNode(pesawat, current);
                    hitCount++;
                    break;
                }
                musuhNode = musuhNode->next;
            }
        }
        current = next;
    }
    return hitCount;
}

void efekNabrakPeluru(Pesawat *pesawat, Musuh *musuh, int unused1, int unused2)
{
    musuh->hp--;
    if (musuh->hp <= 0)
    {
        musuh->aktif = 0;
        playEnemyDeathSound();
        addressuser user = findUser(currentUsername);
        if (user)
        {
            if (musuh->tipe == 1)
            {
                user->score = tambahskormusuhbesar(user->score);
            }
            else
            {
                user->score = tambahskor(user->score);
            }
            cekhighskor(user);
        }
    }
}

void nabrakMusuh(SDL_Renderer *renderer, Pesawat *pesawat, Musuh *musuh)
{
    NodeMusuh *node = headMusuh;
    while (node)
    {
        Musuh *musuh = &node->data;
        if (musuh->aktif &&
            pesawat->x < musuh->x + musuh->w &&
            pesawat->x + pesawat->w > musuh->x &&
            pesawat->y < musuh->y + musuh->h &&
            pesawat->y + pesawat->h > musuh->y)
        {
            if (musuh->tipe == 1)
            {
                pesawat->nyawa -= 2;
            }
            else
            {
                pesawat->nyawa -= 1;
            }

            playPlayerHitSound();
            musuh->aktif = 0;

            if (pesawat->nyawa <= 0)
            {
                kelolaGameOver(renderer);
                return;
            }
        }
        node = node->next;
    }
}

void kelolaGameOver(SDL_Renderer *renderer)
{
    addressuser user = findUser(currentUsername);
    playMusic(gameOverMusic);
    gameover(renderer, user);
    sortLeaderboard();

    // reset skor untuk game berikutnya
    if (user)
        user->score = 0;

    // tunda 2 detik
    SDL_Delay(4000);
    // ubah state ke menu
    state = STATE_MENU;
    playMusic(menuMusic);
    // reset jumlah musuh dan wave untuk game berikutnya
    jumlahmusuh = 5;
    freeWaves(headWave);
    addWave(&headWave, 1);
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

    NodeMusuh *node = headMusuh;
    while (node)
    {
        Musuh *musuh = &node->data;
        if (musuh->aktif)
        {
            float x = musuh->x;
            float y = musuh->y;
            float w = musuh->w;
            float h = musuh->h;

            float TengahanX = x + w / 2;
            float TengahanY = y + h / 2;

            // warna berdasarkan tipe musuh
            SDL_Color currentTubuh = (musuh->tipe == 1) ? warnaTubuhKuat : warnaTubuh;
            SDL_Color currentMata = (musuh->tipe == 1) ? warnaMataKuat : warnaMata;
            SDL_Color currentDetail = (musuh->tipe == 1) ? warnaDetailKuat : warnaDetail;

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
            if (musuh->tipe == 1)
            {
                float hpBarWidth = w * 0.8f;
                float hpBarHeight = h * 0.05f;
                float hpBarX = TengahanX - hpBarWidth / 2;
                float hpBarY = y - hpBarHeight - 5;

                SDL_FRect hpBarBg = {hpBarX, hpBarY, hpBarWidth, hpBarHeight};
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 200);
                SDL_RenderFillRect(renderer, &hpBarBg);

                float hpFill = (float)musuh->hp / 3.0f * hpBarWidth;
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

        node = node->next;
    }
}