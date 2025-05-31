#include "alda.h"
#include <SDL3/SDL_mixer.h>
//deklarasi pointer untuk musik dan efek suara
Mix_Music *menuMusic = NULL;
Mix_Music *gameMusic = NULL;
Mix_Music *gameOverMusic = NULL;

Mix_Chunk *shootSound = NULL;
Mix_Chunk *clickSound = NULL;
Mix_Chunk *enemyDeathSound = NULL;
Mix_Chunk *playerHitSound = NULL;
Mix_Chunk *powerUpHealthSound = NULL;
Mix_Chunk *powerUpAmmoSound = NULL;

// Fungsi inisialisasi SDL_mixer dan memuat musik serta efek suara
void initAudio() {
    // Inisialisasi SDL_mixer
    if (Mix_Init(MIX_INIT_MP3) == 0)
    { 
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
        return;
    }
    
    if (!Mix_OpenAudio(0, NULL)) 
    { 
        printf("SDL_mixer could not open audio! SDL_mixer Error: %s\n", SDL_GetError());
        return;
    }

    // Load musik
    menuMusic = Mix_LoadMUS("assets/audio/menu_music.mp3");
    gameMusic = Mix_LoadMUS("assets/audio/game_music.mp3");
    gameOverMusic = Mix_LoadMUS("assets/audio/game_over.mp3");

    // Load efek suara
    shootSound = Mix_LoadWAV("assets/audio/shoot.wav");
    clickSound = Mix_LoadWAV("assets/audio/click.wav");
    enemyDeathSound = Mix_LoadWAV("assets/audio/enemy_death.wav");
    playerHitSound = Mix_LoadWAV("assets/audio/player_hit.wav");
    powerUpHealthSound = Mix_LoadWAV("assets/audio/nyawa.wav");
    powerUpAmmoSound = Mix_LoadWAV("assets/audio/amunisi.wav");

    // Cek apakah semua file audio berhasil dimuat
    if (!menuMusic || !gameMusic || !gameOverMusic ||!shootSound || !clickSound || !enemyDeathSound || !playerHitSound || !powerUpHealthSound || !powerUpAmmoSound) 
    {
        printf("Failed to load audio files: %s\n", SDL_GetError());
    }
}

// Fungsi memutar musik yang diberikan di parameter
void playMusic(Mix_Music *music) 
{
    // Cek apakah musik yang diberikan tidak NULL
    if (!music) 
    {
        printf("Music file is NULL! Cannot play.\n");
        return;
    }
    
    Mix_HaltMusic();

    // Putar musik menu
    if (Mix_PlayMusic(music, -1) == -1) 
    { 
        printf("Failed to play menu music! SDL_mixer Error: %s\n", SDL_GetError());
    }
}
// Fungsi memutar sound efek tembakan
void playShootSound() 
{ 
    Mix_PlayChannel(-1, shootSound, 0); 
}
// Fungsi memutar sound efek klik button menu
void playClickSound() 
{
    Mix_PlayChannel(-1, clickSound, 0); 
}
// Fungsi memutar sound efek kematian musuh
void playEnemyDeathSound() 
{
    Mix_PlayChannel(-1, enemyDeathSound, 0); 
}
// Fungsi memutar sound efek ketika player bertabrakan dengan musuh
void playPlayerHitSound() 
{
    Mix_PlayChannel(-1, playerHitSound, 0); 
}

void playPowerUpHealthSound() {
    Mix_PlayChannel(-1, powerUpHealthSound, 0);
}

void playPowerUpAmmoSound() {
    Mix_PlayChannel(-1, powerUpAmmoSound, 0);
}
// fungsi untuk menghentikan musik yang sedang diputar
void stopMusic() 
{
    Mix_HaltMusic();
}
// Fungsi untuk menutup audio dan membebaskan sumber daya
void closeAudio() 
{// Bebaskan musik dan tutup SDL_mixer
        Mix_FreeMusic(menuMusic);
        Mix_FreeMusic(gameMusic);
        Mix_FreeMusic(gameOverMusic);
    
        Mix_FreeChunk(shootSound);
        Mix_FreeChunk(clickSound);
        Mix_FreeChunk(enemyDeathSound);
        Mix_FreeChunk(playerHitSound);
    
        Mix_CloseAudio();
        Mix_Quit();
    
}