#ifndef ALDA_H
#define ALDA_H
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>
#include "config.h"

typedef struct
{
    int skor;
    int highskor;
} nilai;

// typedef struct tuser *address;
// typedef struct tuser
// {
//     address prev;
//     char *username;
//     int hskor;
//     address next;
// }user;

extern nilai point;
// extern user pilot;

#include "gema.h"
void tampilskor(SDL_Renderer *renderer, nilai *point);
int tambahskormusuhbesar(int skor);
int tambahskor(int skor);
void cekhighskor(nilai *point);
void loadhighskor(nilai *point);
void simpanhighskor(nilai *point);
void gameover(SDL_Renderer *renderer, nilai *point);

extern Mix_Music *menuMusic;
extern Mix_Music *gameMusic;
extern Mix_Music *gameOverMusic;
extern Mix_Chunk *shootSound;
extern Mix_Chunk *clickSound;
extern Mix_Chunk *enemyDeathSound;
extern Mix_Chunk *playerHitSound;

void initAudio();
void playMusic();
void playShootSound();
void playClickSound();
void playEnemyDeathSound();
void playPlayerHitSound();
void stopMusic();
void closeAudio();

#endif // ALDA_H