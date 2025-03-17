#include "gema.h"
#include "config.h"

// Global renderer (diambil dari main.c)
extern SDL_Renderer *renderer;

void tombolInit(Tombol *tombol, const char *teks, float y, float skalaTeks)
{
    tombol->teks = teks;
    tombol->kotak.x = (LEBAR_LAYAR - LEBAR_TOMBOL) / 2.0f;
    tombol->kotak.y = y;
    tombol->kotak.w = LEBAR_TOMBOL;
    tombol->kotak.h = TINGGI_TOMBOL;
    tombol->skalaTeks = skalaTeks;
    tombol->melayang = false;
}

void tombolUpdateHover(Tombol *tombol, float mouseX, float mouseY)
{
    tombol->melayang = (mouseX >= tombol->kotak.x &&
                        mouseX <= tombol->kotak.x + tombol->kotak.w &&
                        mouseY >= tombol->kotak.y &&
                        mouseY <= tombol->kotak.y + tombol->kotak.h);
}

void tombolRender(Tombol *tombol)
{
    SDL_Color warna = tombol->melayang ? (SDL_Color){100, 100, 255, 255} : (SDL_Color){50, 100, 200, 255};
    SDL_SetRenderDrawColor(renderer, warna.r, warna.g, warna.b, warna.a);
    SDL_RenderFillRect(renderer, &tombol->kotak);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Warna teks putih

    // Menghitung posisi tengah tombol
    float textX = tombol->kotak.x + (tombol->kotak.w / 2) - (strlen(tombol->teks) * 5 * tombol->skalaTeks);
    float textY = tombol->kotak.y + (tombol->kotak.h / 2) - (10 * tombol->skalaTeks);

    SDL_SetRenderScale(renderer, tombol->skalaTeks, tombol->skalaTeks);
    SDL_RenderDebugText(renderer, textX / tombol->skalaTeks, textY / tombol->skalaTeks, tombol->teks);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

bool tombolDiklik(Tombol *tombol, float mouseX, float mouseY)
{
    tombolUpdateHover(tombol, mouseX, mouseY);
    return tombol->melayang;
}

void teksRender(const char *teks, float x, float y, float skala, SDL_Color warna)
{
    SDL_SetRenderDrawColor(renderer, warna.r, warna.g, warna.b, warna.a);
    SDL_SetRenderScale(renderer, skala, skala);
    SDL_RenderDebugText(renderer, x / skala, y / skala, teks);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void menuInit(Menu *menu)
{
    tombolInit(&menu->tombolPlay, "PLAY", TINGGI_LAYAR / 2 - TINGGI_TOMBOL - 10, 1.3f);
    tombolInit(&menu->tombolAbout, "ABOUT", TINGGI_LAYAR / 2 + 10, 1.3f);
}

void menuUpdate(Menu *menu, float mouseX, float mouseY)
{
    tombolUpdateHover(&menu->tombolPlay, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolAbout, mouseX, mouseY);
}

void menuRender(Menu *menu, const Background *background)
{
    renderBackground(background, renderer);

    // Render judul dengan ukuran lebih besar
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Kuning untuk judul
    teksRender("SPACE INVADERS", LEBAR_LAYAR / 2.7f, 120, 3.0f, (SDL_Color){255, 255, 0, 255});

    // Render tombol-tombol
    tombolRender(&menu->tombolPlay);
    tombolRender(&menu->tombolAbout);
}

void aboutRender()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    teksRender("Dibuat oleh: Nama Anda", 200, 100, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("Tekan ESC untuk kembali", 200, 200, 2.0f, (SDL_Color){255, 255, 255, 255});

    SDL_RenderPresent(renderer);
}

void aboutInput(SDL_Event *e, bool *tampilAbout)
{
    if (e->type == SDL_EVENT_KEY_DOWN && e->key.scancode == SDLK_ESCAPE)
    {
        *tampilAbout = false;
    }
}
