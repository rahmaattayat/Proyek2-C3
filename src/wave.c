#include "fairuz.h"
#include <SDL3/SDL.h>
#include "rahma.h"

int waveterbaru = 0; 

void cekmusuh(Musuh musuh[])
{
    bool semuaMusuhMati = true; // Anggap semua musuh sudah mati

    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].aktif)
        {
            semuaMusuhMati = false; // Jika masih ada musuh aktif, belum bisa pindah wave
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

        jumlahmusuh + (waveterbaru * 2); // Tambah 2 musuh setiap wave

        if (jumlahmusuh > MAX_MUSUH)
        {
            jumlahmusuh = MAX_MUSUH; // Batas maksimal
        }
        SDL_Log("jumlah musuh = %d", jumlahmusuh);
        bikinMusuh(musuh, jumlahmusuh, 1, LEBAR_LAYAR, TINGGI_LAYAR);
    }
}
