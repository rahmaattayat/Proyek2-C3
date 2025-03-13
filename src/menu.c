#include "gema.h"
#include "config.h"

// Global renderer (diambil dari main.c)
extern SDL_Renderer *renderer;

void tombolInit(Tombol *tombol, const char *teks, float y)
{
    tombol->teks = teks;
    tombol->kotak.x = (LEBAR_LAYAR - LEBAR_TOMBOL) / 2.0f;
    tombol->kotak.y = y;
    tombol->kotak.w = LEBAR_TOMBOL;
    tombol->kotak.h = TINGGI_TOMBOL;
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
    // Render teks (stub; implementasi nyata dapat memakai SDL_ttf)
    float textX = tombol->kotak.x + 20;
    float textY = tombol->kotak.y + 10;
    teksRender(tombol->teks, textX, textY, 1.5f, (SDL_Color){255, 255, 255, 255});
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
    SDL_RenderDebugText(renderer, x, y, teks);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f); // Kembalikan skala ke normal
}

void menuInit(Menu *menu)
{
    tombolInit(&menu->tombolPlay, "PLAY", TINGGI_LAYAR / 2 - TINGGI_TOMBOL - 10);
    tombolInit(&menu->tombolAbout, "ABOUT", TINGGI_LAYAR / 2 + 10);
}

void menuUpdate(Menu *menu, float mouseX, float mouseY)
{
    tombolUpdateHover(&menu->tombolPlay, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolAbout, mouseX, mouseY);
}

void menuRender(Menu *menu, const Background *background)
{
    // Render background terlebih dahulu
    renderBackground(background, renderer);

    // Render judul (menggunakan SDL_RenderDebugText)
    const char *title = "SPACE INVADERS";
    float titleX = (LEBAR_LAYAR - 960) / 2.0f; // Perkiraan agar berada di tengah
    teksRender(title, titleX, 50, 3.0f, (SDL_Color){255, 255, 0, 255});

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
