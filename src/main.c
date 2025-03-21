#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
Musuh musuh[MAX_MUSUH];
Menu menu;

statusGame state = STATE_MENU;
bool gameBerjalan = true;

nilai point;

void mulai()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Space Invaders - Proyek 2 - C3", LEBAR_LAYAR, TINGGI_LAYAR, 0);
    renderer = SDL_CreateRenderer(window, NULL);

    // inisiasi value record point untuk skor
    point.skor = 0;
    loadhighskor(&point);

    bikinPesawat(&pesawat);
    jumlahmusuh = 5;
    bikinMusuh(musuh, jumlahmusuh, 1, LEBAR_LAYAR, TINGGI_LAYAR);
    bikinBackground(&background, LEBAR_LAYAR, TINGGI_LAYAR);

    menuInit(&menu);
}

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
                reload(&pesawat);
            }
        }
    }
    const Uint8 *keyboard = (const Uint8 *)SDL_GetKeyboardState(NULL);
    gerakinPesawat(&pesawat, keyboard, spasi_dipencet && !spasi_sebelumnya);
}

// Update objek game
void updateGame()
{
    updatePesawat(&pesawat);
    updateReload(&pesawat);
    jalankanPeluru(&pesawat);
    gerakinMusuh(musuh);
    cekmusuh(musuh);
    updateBackground(&background, 1.0f);
    nabrakPeluru(&pesawat, musuh);
    nabrakMusuh(renderer, &pesawat, musuh);
}

void renderGame()
{
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255);
    SDL_RenderClear(renderer);
    renderBackground(&background, renderer);
    bikinGambarPesawat(renderer, &pesawat);
    bikinGambarPeluru(renderer, &pesawat);
    bikinGambarMusuh(renderer, musuh);
    tampilskor(renderer, &point);
    tampilNyawa(renderer, &pesawat);
    tampilAmunisi(renderer, &pesawat);
    tampilkanWave(renderer);

    SDL_RenderPresent(renderer);
}

void restartGame()
{
    point.skor = 0;
    loadhighskor(&point);

    bikinPesawat(&pesawat);
    jumlahmusuh = 5;
    bikinMusuh(musuh, jumlahmusuh, 1, LEBAR_LAYAR, TINGGI_LAYAR);
    bikinBackground(&background, LEBAR_LAYAR, TINGGI_LAYAR);
}

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
            updateMenu(&menu, x, y);
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (tombolDiklik(&menu.tombolPlay, x, y))
                {
                    state = STATE_GAME;
                    restartGame();
                }
                else if (tombolDiklik(&menu.tombolAbout, x, y))
                {
                    state = STATE_ABOUT;
                }
                else if (tombolDiklik(&menu.tombolTutorial, x, y))
                {
                    state = STATE_TUTORIAL;
                }
                else if (tombolDiklik(&menu.tombolExit, x, y))
                {
                    gameBerjalan = false;
                }
            }
        }
    }
}

void buatMenu()
{
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255);
    SDL_RenderClear(renderer);
    renderMenu(&menu, &background);
    SDL_RenderPresent(renderer);
}

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

int SDL_main(int argc, char *argv[])
{
    mulai();

    while (gameBerjalan)
    {
        switch (state)
        {
        case STATE_MENU:
            handleMenuInput();
            updateBackground(&background, 1.0f); // Tambahkan ini untuk update background di menu
            buatMenu();
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
        }
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
