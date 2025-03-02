#include "ihsan.h"
#include <SDL3/SDL.h>

void nembak(Pesawat* pesawat) {
    //find peluru gaaktif
    for (int i = 0; i < MAX_PELURU; i++) {
        if (!pesawat->peluru[i].nyala) {
            pesawat->peluru[i].nyala = true;
            pesawat->peluru[i].x = pesawat->x + pesawat->w;
            pesawat->peluru[i].y = pesawat->y + pesawat->h/2;
            pesawat->peluru[i].dx = 15.0f;//kec tembak
            pesawat->peluru[i].dy = 0;
            return;//debounce
        }
    }
}

void jalankanPeluru(Pesawat* pesawat, int lebarLayar) {
    for (int i = 0; i < MAX_PELURU; i++) {
        if (pesawat->peluru[i].nyala) {
            pesawat->peluru[i].x += pesawat->peluru[i].dx;
            pesawat->peluru[i].y += pesawat->peluru[i].dy;
            
            // matiin peluru klo udh keluar layar
            if (pesawat->peluru[i].x > lebarLayar) {
                pesawat->peluru[i].nyala = false;
            }
        }
    }
}

void bikinGambarPeluru(SDL_Renderer* renderer, Pesawat* pesawat) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//merah(peluru)
    
    for (int i = 0; i < MAX_PELURU; i++) {
        if (pesawat->peluru[i].nyala) {
            SDL_FRect kotakpeluru = {
                pesawat->peluru[i].x, pesawat->peluru[i].y - 2,
                10, 4
            };
            SDL_RenderFillRect(renderer, &kotakpeluru);
            //ekor peluru
            SDL_SetRenderDrawColor(renderer, 255, 200, 0, 150);//kuning ekr
            SDL_FRect ekor = {
                pesawat->peluru[i].x - 8, pesawat->peluru[i].y - 1,
                8, 2
            };
            SDL_RenderFillRect(renderer, &ekor);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//reset warna
        }
    }
}