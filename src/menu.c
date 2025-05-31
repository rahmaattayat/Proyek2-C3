#include "gema.h"
#include "config.h"
#include "ihsan.h"

extern SDL_Renderer *renderer;

void tombolInit(Tombol *tombol, const char *teks, float y, int skalaTeks)
{
    tombol->teks = teks;
    tombol->kotak.x = (LEBAR_LAYAR - LEBAR_TOMBOL) / 2;
    tombol->kotak.y = y;
    tombol->kotak.w = LEBAR_TOMBOL;
    tombol->kotak.h = TINGGI_TOMBOL;
    tombol->skalaTeks = skalaTeks;
    tombol->hover = false;
}

bool TombolHover(const Tombol *tombol, float mouseX, float mouseY)
{
    return (mouseX >= tombol->kotak.x &&
            mouseX <= tombol->kotak.x + tombol->kotak.w &&
            mouseY >= tombol->kotak.y &&
            mouseY <= tombol->kotak.y + tombol->kotak.h);
}

void tombolUpdateHover(Tombol *tombol, float mouseX, float mouseY)
{
    tombol->hover = TombolHover(tombol, mouseX, mouseY);
}

void renderTombol(Tombol *tombol)
{
    SDL_Color warna = tombol->hover ? (SDL_Color){100, 100, 255, 255} : (SDL_Color){50, 100, 200, 255};
    SDL_SetRenderDrawColor(renderer, warna.r, warna.g, warna.b, warna.a);
    SDL_RenderFillRect(renderer, &tombol->kotak);

    int width, height;
    getTextSize(tombol->teks, tombol->skalaTeks, &width, &height);
    float posisiXteks = tombol->kotak.x + (tombol->kotak.w - width) / 2.0f;
    float posisiYTeks = tombol->kotak.y + (tombol->kotak.h - height) / 2.0f;

    renderText(renderer, posisiXteks, posisiYTeks, tombol->teks, tombol->skalaTeks, (SDL_Color){255, 255, 255, 255});
}

// --- TEKS & RENDER UTILITAS ---

void renderIsiMenu(const char **teks, int jumlahBaris, int startX, int startY, int jarakY)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    float skala = 1.3f;
    for (int i = 0; i < jumlahBaris; ++i)
    {
        int width, height;
        getTextSize(teks[i], skala, &width, &height);
        renderText(renderer, startX, startY + i * jarakY, teks[i], skala, (SDL_Color){255, 255, 255, 255});
    }
    SDL_RenderPresent(renderer);
}

// --- MENU UTAMA ---

void menuInit(Menu *menu)
{
    int skala = 1;
    float posisiY = TINGGI_LAYAR / 2 - (TINGGI_TOMBOL * 2);
    tombolInit(&menu->tombolPlay, "PLAY", posisiY, skala);
    tombolInit(&menu->tombolAbout, "ABOUT", posisiY + TINGGI_TOMBOL + 10, skala);
    tombolInit(&menu->tombolTutorial, "TUTORIAL", posisiY + (TINGGI_TOMBOL + 10) * 2, skala);
    tombolInit(&menu->tombolLeaderboard, "LEADERBOARD", posisiY + (TINGGI_TOMBOL + 10) * 3, skala);
    tombolInit(&menu->tombolExit, "EXIT", posisiY + (TINGGI_TOMBOL + 10) * 4, skala);
}

void updateSemuaTombol(Menu *menu, float mouseX, float mouseY)
{
    tombolUpdateHover(&menu->tombolPlay, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolAbout, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolTutorial, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolLeaderboard, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolExit, mouseX, mouseY);
}

void renderTombolMenu(Menu *menu)
{
    renderTombol(&menu->tombolPlay);
    renderTombol(&menu->tombolAbout);
    renderTombol(&menu->tombolTutorial);
    renderTombol(&menu->tombolLeaderboard);
    renderTombol(&menu->tombolExit);
}

void renderMenu(Menu *menu, const Background *background)
{
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255);
    SDL_RenderClear(renderer);
    renderBackground(background, renderer);

    int width, height;
    float skala = 2.5f;
    getTextSize("C3 - SPACE INVADERS", skala, &width, &height);
    renderText(renderer, (LEBAR_LAYAR - width) / 2.0f, 120, "C3 - SPACE INVADERS", skala, (SDL_Color){255, 255, 0, 255});

    renderTombolMenu(menu);
    SDL_RenderPresent(renderer);
}

// --- HALAMAN ABOUT DAN TUTORIAL ---

void renderAbout()
{
    const char *teks[] = {
        "Dibuat oleh: Kelompok C3",
        "1. Alda Pujama (241511066)",
        "2. Fairuz Sheva M (241511073)",
        "3. Gema Adzan F (241511075)",
        "4. Muhammad Ihsan R (241511083)",
        "5. Rahma Attaya T (241511088)",
        "Tekan ESC untuk kembali"};
    renderIsiMenu(teks, 7, 200, 100, 30);
}

void renderTutorial()
{
    const char *teks[] = {
        "1. Pada layar menu, pilih opsi PLAY untuk memulai permainan",
        "2. Gunakan W untuk ke atas, S ke bawah, A kiri, D kanan",
        "3. Tekan SPACE untuk menembak (ada cooldown)",
        "4. Tekan R untuk reload saat amunisi habis",
        "5. Ambil power-up untuk nyawa atau peluru tambahan",
        "6. Hindari tabrakan dengan musuh karena bisa mengurangi nyawa",
        "Tekan ESC untuk kembali"};
    renderIsiMenu(teks, 7, 200, 100, 35);
}