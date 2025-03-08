#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //buat random
#include "ihsan.h"
#include "gema.h"
#include "rahma.h"

#define LAYAR_LEBAR 1280
#define LAYAR_TINGGI 720
int layar[2] = {1280, 720}; // layar[LEBAR] = 1280 ama layar[TINGGI] = 720

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Pesawat pesawat;
Background bg;
bool spasi_dipencet = false;
bool spasi_sebelumnya = false;
Musuh musuh;

void mulai()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Space Invaders - Proyek 2 - C3", layar[LEBAR], layar[TINGGI], 0);
    renderer = SDL_CreateRenderer(window, NULL);

    bikinPesawat(&pesawat);
    bikinMusuh(&musuh, LAYAR_LEBAR, LAYAR_TINGGI);
    bikinBackground(&bg, layar[LEBAR], layar[TINGGI]);
}

void cekInput()
{
    SDL_Event event;
    // biar ga spam tembak(debounce)
    spasi_sebelumnya = spasi_dipencet;
    spasi_dipencet = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            SDL_Quit();
            exit(0);
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_SPACE)
            {
                spasi_dipencet = true;
            }
        }
    }

    const Uint8 *keyboard = (const Uint8 *)SDL_GetKeyboardState(NULL);
    gerakinPesawat(&pesawat, keyboard, spasi_dipencet && !spasi_sebelumnya);
}

void update()
{
    updatePesawat(&pesawat);
    jalankanPeluru(&pesawat);
    gerakinMusuh(&musuh);
    updateBackground(&bg, 1.0f);

    if (musuh.x + musuh.w < 0)
    {
        bikinMusuh(&musuh, LAYAR_LEBAR, LAYAR_TINGGI);
    }
}

void gambar()
{
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255);
    SDL_RenderClear(renderer);
    renderBackground(&bg, renderer);
    bikinGambarPesawat(renderer, &pesawat);
    bikinGambarPeluru(renderer, &pesawat);
    bikinGambarMusuh(renderer, &musuh);
    SDL_RenderPresent(renderer);
}

int SDL_main(int argc, char *argv[])
{
    mulai();

    while (1)
    {
        cekInput();
        update();
        gambar();
        SDL_Delay(16); // buat 60 fps, harusnya sih
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}