#include "gema.h"
#include "config.h"

extern SDL_Renderer *renderer;

void tombolInit(Tombol *tombol, const char *teks, float y, float skalaTeks)
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

    int lebarHuruf = 8;
    int tinggiBaris = 10;

    float lebarTeks = strlen(tombol->teks) * lebarHuruf * tombol->skalaTeks;
    float tinggiTeks = tinggiBaris * tombol->skalaTeks;

    float posisiXteks = tombol->kotak.x + (tombol->kotak.w - lebarTeks) / 2;
    float posisiYTeks = tombol->kotak.y + (tombol->kotak.h - tinggiTeks) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_SetRenderScale(renderer, tombol->skalaTeks, tombol->skalaTeks);
    SDL_RenderDebugText(renderer, posisiXteks / tombol->skalaTeks, posisiYTeks / tombol->skalaTeks, tombol->teks);
    SDL_SetRenderScale(renderer, 1, 1);
}

// --- TEKS & RENDER UTILITAS ---

void teksRender(const char *teks, float x, float y, float skala, SDL_Color warna)
{
    SDL_SetRenderDrawColor(renderer, warna.r, warna.g, warna.b, warna.a);
    SDL_SetRenderScale(renderer, skala, skala);
    SDL_RenderDebugText(renderer, x / skala, y / skala, teks);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

float posisiTeksTengahX(const char *teks, float skala)
{
    float lebarHuruf = 8;
    float lebarTeks = strlen(teks) * lebarHuruf * skala;
    return (LEBAR_LAYAR - lebarTeks) / 2;
}

void teksRenderTengah(const char *teks, float y, float skala, SDL_Color warna)
{
    float x = posisiTeksTengahX(teks, skala);
    teksRender(teks, x, y, skala, warna);
}

void renderHalamanStatik(const char **teks, int jumlahBaris, float startX, float startY, float jarakY)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < jumlahBaris; ++i)
    {
        teksRender(teks[i], startX, startY + i * jarakY, 2.0f, (SDL_Color){255, 255, 255, 255});
    }
    SDL_RenderPresent(renderer);
}

// --- MENU UTAMA ---

void menuInit(Menu *menu)
{
    float posisiY = TINGGI_LAYAR / 2 - (TINGGI_TOMBOL * 2);
    tombolInit(&menu->tombolPlay, "PLAY", posisiY, 1.3f);
    tombolInit(&menu->tombolAbout, "ABOUT", posisiY + TINGGI_TOMBOL + 10, 1.3f);
    tombolInit(&menu->tombolTutorial, "TUTORIAL", posisiY + (TINGGI_TOMBOL + 10) * 2, 1.3f);
    tombolInit(&menu->tombolExit, "EXIT", posisiY + (TINGGI_TOMBOL + 10) * 3, 1.3f);
}

void tombolUpdateSemua(Menu *menu, float mouseX, float mouseY)
{
    tombolUpdateHover(&menu->tombolPlay, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolAbout, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolTutorial, mouseX, mouseY);
    tombolUpdateHover(&menu->tombolExit, mouseX, mouseY);
}

void updateMenu(Menu *menu, float mouseX, float mouseY)
{
    tombolUpdateSemua(menu, mouseX, mouseY);
}

void renderTombolMenu(Menu *menu)
{
    renderTombol(&menu->tombolPlay);
    renderTombol(&menu->tombolAbout);
    renderTombol(&menu->tombolTutorial);
    renderTombol(&menu->tombolExit);
}

void renderMenu(Menu *menu, const Background *background)
{
    addressuser user = findUser(currentUsername);
    renderBackground(background, renderer);

    teksRenderTengah("C3 - SPACE INVADERS", 120, 3.0f, (SDL_Color){255, 255, 0, 255});

    char teksHighSkor[50];
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", user->hskor);
    teksRenderTengah(teksHighSkor, 180, 1.5f, (SDL_Color){255, 255, 0, 255});

    renderTombolMenu(menu);
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
    renderHalamanStatik(teks, 7, 200, 100, 30);
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
    renderHalamanStatik(teks, 7, 200, 100, 35);
}
