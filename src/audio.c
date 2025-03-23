#include "alda.h"
#include <SDL3/SDL_mixer.h>

Mix_Music *menuMusic = NULL;
Mix_Music *gameMusic = NULL;
Mix_Music *gameOverMusic = NULL;

Mix_Chunk *shootSound = NULL;
Mix_Chunk *clickSound = NULL;
Mix_Chunk *enemyDeathSound = NULL;
Mix_Chunk *playerHitSound = NULL;

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

    if (!menuMusic || !gameMusic || !gameOverMusic ||!shootSound || !clickSound || !enemyDeathSound || !playerHitSound) 
    {
        printf("Failed to load audio files: %s\n", SDL_GetError());
    }
}

void playMusic(Mix_Music *music) 
{
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

void playShootSound() { Mix_PlayChannel(-1, shootSound, 0); }

void playClickSound() { Mix_PlayChannel(-1, clickSound, 0); }

void playEnemyDeathSound() { Mix_PlayChannel(-1, enemyDeathSound, 0); }

void playPlayerHitSound() { Mix_PlayChannel(-1, playerHitSound, 0); }

void stopMusic() {
    // Hentikan musik yang sedang diputar
    Mix_HaltMusic();
}
    
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