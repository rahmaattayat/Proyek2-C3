#include "gema.h"
#include "config.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <string.h>
#include <stdio.h>

extern SDL_Renderer *renderer;
extern TTF_Font *font;

// --- TOMBOL ---

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

    // Teks di tengah tombol
    TTF_SetFontSize(font, (int)(24 * tombol->skalaTeks)); // Apply scaling
    int w, h;
    if (!TTF_GetStringSize(font, tombol->teks, 0, &w, &h))
    {
        printf("Failed to measure text: %s\n", SDL_GetError());
        TTF_SetFontSize(font, 24); // Reset font size
        return;
    }

    float posisiX = tombol->kotak.x + (tombol->kotak.w - w) / 2;
    float posisiY = tombol->kotak.y + (tombol->kotak.h - h) / 2;

    renderText(renderer, posisiX, posisiY, tombol->teks, (SDL_Color){255, 255, 255, 255});
    TTF_SetFontSize(font, 24); // Reset font size
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

void renderMenu(Menu *menu, const Background *background, nilai *point)
{
    renderBackground(background, renderer);

    // Judul
    const char *judul = "C3 - SPACE INVADERS";
    TTF_SetFontSize(font, (int)(24 * 3.0f)); // Scale for title
    int w, h;
    if (!TTF_GetStringSize(font, judul, 0, &w, &h))
    {
        printf("Failed to measure title text: %s\n", SDL_GetError());
        TTF_SetFontSize(font, 24);
        return;
    }

    renderText(renderer, (LEBAR_LAYAR - w) / 2, 120, judul, (SDL_Color){255, 255, 0, 255});

    // High Skor
    char teksHighSkor[50];
    snprintf(teksHighSkor, sizeof(teksHighSkor), "High Skor: %d", point->highskor);
    TTF_SetFontSize(font, (int)(24 * 1.5f)); // Scale for high score
    if (!TTF_GetStringSize(font, teksHighSkor, 0, &w, &h))
    {
        printf("Failed to measure high score text: %s\n", SDL_GetError());
        TTF_SetFontSize(font, 24);
        return;
    }

    renderText(renderer, (LEBAR_LAYAR - w) / 2, 180, teksHighSkor, (SDL_Color){255, 255, 0, 255});
    TTF_SetFontSize(font, 24); // Reset font size

    renderTombolMenu(menu);
}

// --- HALAMAN ABOUT DAN TUTORIAL ---

void renderHalamanStatik(const char **teks, int jumlahBaris, float startX, float startY, float jarakY)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_SetFontSize(font, (int)(24 * 1.0f)); // No scaling for static pages
    for (int i = 0; i < jumlahBaris; ++i)
    {
        renderText(renderer, startX, startY + i * jarakY, teks[i], (SDL_Color){255, 255, 255, 255});
    }

    TTF_SetFontSize(font, 24); // Reset font size
    SDL_RenderPresent(renderer);
}

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