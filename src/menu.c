#include "gema.h"
#include "config.h"

extern SDL_Renderer *renderer;

void tombolInit(Tombol *tombol, const char *teks, float y, float skalaTeks)
{
    tombol->teks = teks;
    tombol->kotak.x = (LEBAR_LAYAR - LEBAR_TOMBOL) / 2.0f;
    tombol->kotak.y = y;
    tombol->kotak.w = LEBAR_TOMBOL;
    tombol->kotak.h = TINGGI_TOMBOL;
    tombol->skalaTeks = skalaTeks;
    tombol->hover = false;
}

void tombolUpdateHover(Tombol *tombol, float mouseX, float mouseY)
{
    tombol->hover = (mouseX >= tombol->kotak.x &&
                     mouseX <= tombol->kotak.x + tombol->kotak.w &&
                     mouseY >= tombol->kotak.y &&
                     mouseY <= tombol->kotak.y + tombol->kotak.h);
}

void renderTombol(Tombol *tombol)
{

    SDL_Color warna = tombol->hover ? (SDL_Color){100, 100, 255, 255} : (SDL_Color){50, 100, 200, 255};
    SDL_SetRenderDrawColor(renderer, warna.r, warna.g, warna.b, warna.a);
    SDL_RenderFillRect(renderer, &tombol->kotak);

    float lebarHuruf = 8.0f;
    float tinggiBaris = 10.0f;

    float lebarTeks = strlen(tombol->teks) * lebarHuruf * tombol->skalaTeks;
    float tinggiTeks = tinggiBaris * tombol->skalaTeks;

    float posisiXteks = tombol->kotak.x + (tombol->kotak.w - lebarTeks) / 2;
    float posisiYTeks = tombol->kotak.y + (tombol->kotak.h - tinggiTeks) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_SetRenderScale(renderer, tombol->skalaTeks, tombol->skalaTeks);
    SDL_RenderDebugText(
        renderer,
        posisiXteks / tombol->skalaTeks,
        posisiYTeks / tombol->skalaTeks,
        tombol->teks);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

bool tombolDiklik(Tombol *tombol, float mouseX, float mouseY)
{
    tombolUpdateHover(tombol, mouseX, mouseY);
    return tombol->hover;
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
    float posisiY = TINGGI_LAYAR / 2 - (TINGGI_TOMBOL * 2 + 0);
    tombolInit(&menu->tombolPlay, "PLAY", posisiY, 1.3f);
    tombolInit(&menu->tombolAbout, "ABOUT", posisiY + TINGGI_TOMBOL + 10, 1.3f);
    tombolInit(&menu->tombolTutorial, "TUTORIAL", posisiY + (TINGGI_TOMBOL + 10) * 2, 1.3f);
    tombolInit(&menu->tombolExit, "EXIT", posisiY + (TINGGI_TOMBOL + 10) * 3, 1.3f);
}

void updateMenu(Menu *menu, float mouseX, float mouseY)
{
    tombolUpdateHover(&menu->tombolPlay, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolAbout, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolTutorial, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolExit, mouseX, mouseY);
}

void renderMenu(Menu *menu, const Background *background, nilai *point)
{
    renderBackground(background, renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    teksRender("C3 - SPACE INVADERS", LEBAR_LAYAR / 3.0f, 120, 3.0f, (SDL_Color){255, 255, 0, 255});

    char teksHighSkor[50];
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", point->highskor);
    teksRender(teksHighSkor, LEBAR_LAYAR / 2.3f, 180, 1.5f, (SDL_Color){255, 255, 0, 255});

    // Render tombol-tombol
    renderTombol(&menu->tombolPlay);
    renderTombol(&menu->tombolAbout);
    renderTombol(&menu->tombolTutorial);
    renderTombol(&menu->tombolExit);
}

void renderAbout()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    teksRender("Dibuat oleh: Kelompok C3", 200, 100, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("1. Alda Pujama (241511066)", 200, 130, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("2. Fairuz Sheva M (241511073)", 200, 160, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("3. Gema Adzan F (241511075)", 200, 190, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("4. Muhammad Ihsan R (241511083)", 200, 220, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("5. Rahma Attaya T (241511088)", 200, 250, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("Tekan ESC untuk kembali", 200, 350, 2.0f, (SDL_Color){255, 255, 255, 255});
    SDL_RenderPresent(renderer);
}

void renderTutorial()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    teksRender("'WASD' UNTUK MENGGERAKAN PESAWAT", 200, 100, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("'SPACE' UNTUK MENEMBAK", 200, 130, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("'R' UNTUK MENGISI AMUNISI", 200, 160, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("Pastikan jangan ada musuh yang terlewat", 200, 190, 2.0f, (SDL_Color){255, 255, 255, 255});
    teksRender("Tekan ESC untuk kembali", 200, 290, 2.0f, (SDL_Color){255, 255, 255, 255});
    SDL_RenderPresent(renderer);
}
