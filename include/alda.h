#ifndef ALDA_H
#define ALDA_H
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>
#include "config.h"

// typedef struct
// {
//     int skor;
//     int highskor;
// } nilai;

typedef struct tuser *addressuser;
typedef struct tuser
{
    addressuser prevuser;
    char username[50];
    int score;
    int hskor;
    addressuser nextuser;
} user;

//extern nilai point;
extern addressuser headuser;
extern addressuser tailuser;
extern char currentUsername[50];


#include "gema.h"
void tampilskor(SDL_Renderer *renderer);
int tambahskormusuhbesar(int skor);
int tambahskor(int skor);
void cekhighskor(addressuser user);
// void loadhighskor(nilai *point);
// void simpanhighskor(nilai *point);
void gameover(SDL_Renderer *renderer, addressuser user);

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

void loadLeaderboard();
void saveLeaderboard();
void freeLeaderboard();
void insertUser(const char *username, int score, int hskor);
addressuser findUser(const char *username);
void sortLeaderboard();
#endif // ALDA_H