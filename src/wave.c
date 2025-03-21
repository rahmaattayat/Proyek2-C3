#include "fairuz.h"
#include <SDL3/SDL.h>
#include "rahma.h"

int waveterbaru = 1;

void cekmusuh(Musuh *musuh)
{
    bool semuaMusuhMati = true;

    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].aktif)
        {
            semuaMusuhMati = false;
            return;
        }
    }
    updatewave(musuh);
}

void updatewave(Musuh *musuh)
{
    if (waveterbaru < MAX_WAVE - 1)
    {
        (waveterbaru)++;

        tambahmusuh(musuh);

        if (jumlahmusuh > MAX_MUSUH)
        {
            jumlahmusuh = MAX_MUSUH;
        }
        SDL_Log("jumlah musuh = %d", jumlahmusuh);
        bikinMusuh(musuh, jumlahmusuh, 1, LEBAR_LAYAR, TINGGI_LAYAR);
    }
}

void tampilkanWave(SDL_Renderer *renderer)
{
    char teksWave[20];
    sprintf(teksWave, "WAVE %d", waveterbaru);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDebugText(renderer, (LEBAR_LAYAR / 2) - 40, 22, teksWave);
}

void tambahmusuh(Musuh *musuh)
{
    jumlahmusuh = jumlahmusuh + waveterbaru;
}