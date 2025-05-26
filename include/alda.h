#ifndef ALDA_H
#define ALDA_H
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>
#include "config.h"
//struk yang digunakan untuk menyimpan data pemain
typedef struct tuser *addressuser;
typedef struct tuser
{
    addressuser prevuser;
    char username[50];
    int score;
    int hskor;
    addressuser nextuser;
} user;
//mengglobalkan variable karena akan digunakan di beberapa file
extern addressuser headuser;
extern addressuser tailuser;
extern char currentUsername[50];

// protoype fungsi yang mengatur skor dan gameover
#include "gema.h"
void tampilskor(SDL_Renderer *renderer);
int tambahskormusuhbesar(int skor);
int tambahskor(int skor);
void cekhighskor(addressuser user);
void gameover(SDL_Renderer *renderer, addressuser user);

//menglobalkan variable yang digunakan untuk musik dan suara
extern Mix_Music *menuMusic;
extern Mix_Music *gameMusic;
extern Mix_Music *gameOverMusic;
extern Mix_Chunk *shootSound;
extern Mix_Chunk *clickSound;
extern Mix_Chunk *enemyDeathSound;
extern Mix_Chunk *playerHitSound;
//protoype fungsi yang mengatur musik dan suara
void initAudio();
void playMusic();
void playShootSound();
void playClickSound();
void playEnemyDeathSound();
void playPlayerHitSound();
void stopMusic();
void closeAudio();
//protoype fungsi yang mengatur leaderboard
void loadLeaderboard();
void saveLeaderboard();
void freeLeaderboard();
void insertUser(const char *username, int score, int hskor);
addressuser findUser(const char *username);
void sortLeaderboard();
#endif // ALDA_H