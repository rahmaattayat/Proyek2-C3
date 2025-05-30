#ifndef CONFIG_H
#define CONFIG_H

// Screen dimensions
#define LEBAR_LAYAR 1280
#define TINGGI_LAYAR 720

// status game
typedef enum
{
    STATE_MENU,
    STATE_USERINPUT,
    STATE_GAME,
    STATE_ABOUT,
    STATE_TUTORIAL,
    STATE_LEADERBOARD
} statusGame;
#endif // CONFIG_H