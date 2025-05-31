#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "ihsan.h"
#include "rahma.h"
#include "gema.h"
#include "alda.h"
#include "fairuz.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Pesawat pesawat;
Background background;
Menu menu;

statusGame state = STATE_MENU;
bool gameBerjalan = true;
// deklarasi awal variable untuk input username
char inputBuffer[50] = "";
int inputLength = 0;

int rentangMinimum = 30;
int rentangMaksimum = 40;
// deklarasi awal pointer yang menunjuk awal dan akhir linked list
addressuser headuser = NULL;
addressuser tailuser = NULL;

// fungsi untuk apa yang harus dilakukan saat program dimulai
void mulai()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Space Invaders - Proyek 2 - C3", LEBAR_LAYAR, TINGGI_LAYAR, 0);
    renderer = SDL_CreateRenderer(window, NULL);

    initAudio();
    playMusic(menuMusic);
    initTTF();
    loadLeaderboard();

    bikinPesawat(&pesawat);
    addWave(&headWave, 1);
    jumlahmusuh = 5;
    bikinMusuh(jumlahmusuh);
    bikinBackground(&background, LEBAR_LAYAR, TINGGI_LAYAR);
    loadTeksturSuplai(renderer);

    menuInit(&menu);
    waktuTerakhirSuplai = SDL_GetTicks();
    rentangSpawnSuplai = (rand() % (rentangMaksimum - rentangMinimum + 1) + rentangMinimum) * 1000;
}
// fungsi untuk mengelola input dari pengguna saat game
void cekInput()
{
    SDL_Event event;
    static bool spasi_dipencet = false;
    static bool spasi_sebelumnya = false;
    spasi_sebelumnya = spasi_dipencet;
    spasi_dipencet = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            gameBerjalan = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_SPACE)
            {
                spasi_dipencet = true;
            }
            else if (event.key.scancode == SDL_SCANCODE_R)
            {
                if (reload(&pesawat))
                {
                    printf("Reload dimulai!\n");
                }
                else
                {
                    printf("Reload gagal!\n");
                }
            }
        }
    }
    const Uint8 *keyboard = (const Uint8 *)SDL_GetKeyboardState(NULL);
    gerakinPesawat(&pesawat, keyboard, spasi_dipencet && !spasi_sebelumnya);
}

// fungsi untuk update objek game
void updateGame()
{
    updatePesawat(&pesawat);
    updateReload(&pesawat);
    jalankanPeluru(&pesawat);
    gerakinMusuh();
    musuhKeluarLayar();
    cekmusuh();
    updateBackground(&background, 1.0f);
    nabrakPeluru(&pesawat);
    nabrakMusuh(renderer, &pesawat);
    updateSuplai(renderer, &pesawat);

    Uint32 waktuSekarang = SDL_GetTicks();
    if (waktuSekarang - waktuTerakhirSuplai >= rentangSpawnSuplai)
    {
        int jenis = rand() % JENIS_SUPLAI;
        if (spawnSuplai(jenis))
        {
            if (jenis == 0)
            {
                printf("Suplai nyawa berhasil di-spawn.\n");
            }
            else if (jenis == 1)
            {
                printf("Suplai amunisi berhasil di-spawn.\n");
            }
        }
        waktuTerakhirSuplai = waktuSekarang;
        rentangSpawnSuplai = (rand() % (rentangMaksimum - rentangMinimum + 1) + rentangMinimum) * 1000;
    }
}
// fungsi untuk render objek game
void renderGame()
{
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255);
    SDL_RenderClear(renderer);
    renderBackground(&background, renderer);
    bikinGambarPesawat(renderer, &pesawat);
    bikinGambarPeluru(renderer, &pesawat);
    bikinGambarMusuh(renderer);
    renderSuplai(renderer);
    tampilskor(renderer);
    tampilNyawa(renderer, &pesawat);
    tampilAmunisi(renderer, &pesawat);
    tampilkanWave(renderer);

    SDL_RenderPresent(renderer);
}
// fungsi untuk mereset game
void restartGame()
{
    addressuser user = findUser(currentUsername);
    if (user) user->score = 0;

    bikinPesawat(&pesawat);
    jumlahmusuh = 5;
    bikinMusuh(jumlahmusuh);
    bikinBackground(&background, LEBAR_LAYAR, TINGGI_LAYAR);
    bonus = 1;
}
// fungsi untuk mengelola input dari menu
void handleMenuInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            gameBerjalan = false;
        }
        else if (event.type == SDL_EVENT_MOUSE_MOTION || event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            float x, y;
            SDL_GetMouseState(&x, &y);
            updateSemuaTombol(&menu, x, y); 

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if (TombolHover(&menu.tombolPlay, x, y))
                {
                    // playClickSound();
                    // playMusic(gameMusic);
                    // state = STATE_GAME;
                    // restartGame();
                    playClickSound();
                    SDL_StartTextInput(window);  // mulai input teks SDL
                    inputBuffer[0] = '\0';
                    inputLength = 0;
                    state = STATE_USERINPUT;
                }
                else if (TombolHover(&menu.tombolAbout, x, y))
                {
                    playClickSound();
                    state = STATE_ABOUT;
                }
                else if (TombolHover(&menu.tombolTutorial, x, y))
                {
                    playClickSound();
                    state = STATE_TUTORIAL;
                }
                else if (TombolHover(&menu.tombolLeaderboard, x, y))
                {
                    playClickSound();
                    state = STATE_LEADERBOARD;
                }
                else if (TombolHover(&menu.tombolExit, x, y))
                {
                    playClickSound();
                    gameBerjalan = false;
                }
            }
        }
    }
}
// fungsi untuk menangani input username dan masuk ke state game
void handleInputUsername(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            gameBerjalan = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            SDL_Scancode sc = event.key.scancode;
            if (sc == SDL_SCANCODE_RETURN || sc == SDL_SCANCODE_KP_ENTER) {
                strncpy(currentUsername, inputBuffer, sizeof(currentUsername));
                currentUsername[sizeof(currentUsername) - 1] = '\0';

                addressuser existing = findUser(currentUsername);
                if (!existing) {
                    insertUser(currentUsername, 0, 0);
                }
                SDL_StopTextInput(window);
                playMusic(gameMusic);
                state = STATE_GAME;
                restartGame();
                inputBuffer[0] = '\0';
                inputLength = 0;
            } else if (sc == SDL_SCANCODE_BACKSPACE && inputLength > 0) {
                inputBuffer[--inputLength] = '\0';
            }
        } else if (event.type == SDL_EVENT_TEXT_INPUT) {
            if (inputLength < sizeof(inputBuffer) - 1) {
                strcat(inputBuffer, event.text.text);
                inputLength++;
            }
        }
    }
}
// fungsi untuk tampilan input username
void renderInputUsername(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255);
    SDL_RenderClear(renderer);

    float skala1 = 2.0f;
    float skala2 = 2.0f;
    float skala3 = 1.0f;
    int width, height;

    getTextSize("MASUKKAN USERNAME", skala1, &width, &height);
    renderText(renderer, (LEBAR_LAYAR - width) / 2.0f, 180, "MASUKKAN USERNAME", skala1, (SDL_Color){255, 255, 0, 255});

    if (inputLength > 0)
    {
        getTextSize(inputBuffer, skala2, &width, &height);
        renderText(renderer, (LEBAR_LAYAR - width) / 2.0f, 260, inputBuffer, skala2, (SDL_Color){255, 255, 255, 255});
    }

    getTextSize("Tekan ENTER untuk lanjut", skala3, &width, &height);
    renderText(renderer, (LEBAR_LAYAR - width) / 2.0f, 350, "Tekan ENTER untuk lanjut", skala3, (SDL_Color){200, 200, 200, 255});

    SDL_RenderPresent(renderer);
}
// fungsi untuk menangani input pada halaman About
void inputAbout()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            gameBerjalan = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
        {
            state = STATE_MENU;
        }
    }
    renderAbout();
}
// fungsi untuk menangani input pada halaman Tutorial
void inputTutorial()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            gameBerjalan = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
        {
            state = STATE_MENU;
        }
    }
    renderTutorial();
}
// fungsi untuk menangani input pada halaman Leaderboard
void inputLeaderboard()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            gameBerjalan = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
        {
            state = STATE_MENU;
        }
    }
    updateBackground(&background, 1.0f);
    renderLeaderboard(renderer, &background);
}
// fungsi utama yang menjalankan game
int SDL_main(int argc, char *argv[])
{
    srand(time(NULL));
    mulai();

    while (gameBerjalan)
    {
        switch (state)
        {
        case STATE_MENU:
            handleMenuInput();
            updateBackground(&background, 1.0f);
            renderMenu(&menu, &background);
            break;
        case STATE_USERINPUT:
            handleInputUsername();
            renderInputUsername(renderer);
            break;
        case STATE_GAME:
            cekInput();
            updateGame();
            renderGame();
            break;
        case STATE_ABOUT:
            inputAbout();
            break;
        case STATE_TUTORIAL:
            inputTutorial();
            renderTutorial();
            break;
        case STATE_LEADERBOARD:
            inputLeaderboard();
            break;
        }
        SDL_Delay(16);
    }
    hapusTeksturSuplai();
    clearSuplai();
    saveLeaderboard();
    freeLeaderboard();
    stopMusic();
    closeAudio();

    cleanupTTF();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}