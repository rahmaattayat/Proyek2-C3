#include "fairuz.h"
#include <SDL3/SDL.h>

void cekmusuh( Musuh musuh[]) 
{
    int semuaMusuhMati = 1;  // Anggap semua musuh sudah mati

    for (int i = 0; i < JUMLAH; i++) {
        if (musuh[i].aktif) {
            semuaMusuhMati = 0;  // Jika masih ada musuh aktif, belum bisa pindah wave
            break;
        }
    }
}