#include <string.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include "alda.h"
#include "ihsan.h"

// deklarasi awal untuk variable currentUsername
char currentUsername[50] = "";

// Fungsi untuk membuka file leaderboard.dat dan memanggil fungsi insertUser
void loadLeaderboard()
{
    FILE *file = fopen("src/leaderboard.dat", "r");
    if (!file)
    {
        printf("File leaderboard.dat tidak ditemukan\n");
        return;
    }
    if (file)
    {
        char username[50];
        int hskor, score;
        while (fscanf(file, "%s %d %d\n", username, &score, &hskor) == 3)
        {
            insertUser(username, score, hskor);
        }
        printf("File leaderboard.dat sudah dimasukan ke linked list\n");
        fclose(file);
    }
}

// Fungsi untuk memasukkan user baru ke dalam linked list
void insertUser(const char *username, int score, int hskor)
{
    int count = 0;
    addressuser temp = headuser;
    while (temp != NULL)
    {
        count++;
        temp = temp->nextuser;
    }
    if (count > 50)
    {
        printf("Leaderboard sudah penuh, tidak bisa menambah user baru.\n");
        return;
    }

    addressuser newUser = (addressuser)malloc(sizeof(user));
    if (!newUser)
    {
        printf("gagal malloc newuser di insertuser\n");
        return;
    }

    strcpy(newUser->username, username);
    newUser->score = score;
    newUser->hskor = hskor;
    newUser->nextuser = NULL;
    newUser->prevuser = NULL;

    if (headuser == NULL)
    {
        headuser = tailuser = newUser;
    }
    else
    {
        tailuser->nextuser = newUser;
        newUser->prevuser = tailuser;
        tailuser = newUser;
    }
}

// Fungsi untuk mencari user berdasarkan username
addressuser findUser(const char *username)
{
    addressuser current = headuser;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
        {
            return current;
        }
        current = current->nextuser;
    }
    return NULL;
}

// Fungsi untuk mengurutkan linkedlist berdasarkan highskor tertinggi
void sortLeaderboard()
{
    if (headuser == NULL || headuser->nextuser == NULL)
        return;

    bool swapped;
    addressuser current;
    addressuser last = NULL;

    do
    {
        swapped = false;
        current = headuser;

        while (current->nextuser != last)
        {
            if (current->hskor < current->nextuser->hskor)
            {
                // Simpan pointer sementara
                addressuser next = current->nextuser;
                addressuser prev = current->prevuser;
                addressuser nextNext = next->nextuser;

                // Perbarui pointer sekitar current dan next
                if (prev != NULL)
                {
                    prev->nextuser = next;
                }
                else
                {
                    headuser = next;
                }
                next->prevuser = prev;

                if (nextNext != NULL)
                {
                    nextNext->prevuser = current;
                }
                else
                {
                    tailuser = current;
                }
                current->nextuser = nextNext;

                next->nextuser = current;
                current->prevuser = next;

                swapped = true;
            }
            else
            {
                current = current->nextuser;
            }
        }
        last = current;
    } while (swapped);
}

// Fungsi untuk menyimpan data pemain dari linked list ke file leaderboard.dat
void saveLeaderboard()
{
    FILE *file = fopen("src/leaderboard.dat", "w");
    if (!file)
    {
        printf("File leaderboard.dat tidak ditemukan\n");
        return;
    }
    if (file)
    {
        addressuser current = headuser;
        int count = 0;
        while (current != NULL && count < 50)
        {
            fprintf(file, "%s %d %d\n", current->username, current->score, current->hskor);
            current = current->nextuser;
            count++;
        }
        printf("linked list sudah dimasukan ke File leaderboard.dat\n");
        fclose(file);
    }
}

// Fungsi untuk membebaskan memori yang digunakan oleh linked list
void freeLeaderboard()
{
    addressuser current = headuser;
    while (current != NULL)
    {
        addressuser temp = current;
        current = current->nextuser;
        free(temp);
    }
    headuser = NULL;
    tailuser = NULL;
}

// Function to render the leaderboard with stars
void renderLeaderboard(SDL_Renderer *renderer, const Background *background)
{
    SDL_SetRenderDrawColor(renderer, 0, 5, 20, 255); // Dark background
    SDL_RenderClear(renderer);

    // Render stars from the background
    renderBackground(background, renderer);
    SDL_Color kuning = {255, 255, 0, 0};

    // Render leaderboard title
    int width, height;
    float scale = 3.0f;
    getTextSize("LEADER BOARD", scale, &width, &height);
    renderText(renderer, (LEBAR_LAYAR - width) / 2.0f, 50, "LEADER BOARD", scale, kuning);

    // Render table headers with wider spacing for 1080px width
    scale = 1.5f;
    getTextSize("No", scale, &width, &height);
    renderText(renderer, 400 - width / 2.0f, 150, "No", scale, kuning);
    getTextSize("Nama Pilot (username)", scale, &width, &height);
    renderText(renderer, 750 - width / 2.0f, 150, "Username", scale, kuning);
    getTextSize("Highskor", scale, &width, &height);
    renderText(renderer, 900 - width / 2.0f, 150, "Highskor", scale, kuning);
    // Render leaderboard entries with wider spacing
    addressuser current = headuser;
    int count = 1;
    float yPos = 190;
    while (current != NULL && count <= 10)
    { // Display top 10
        char noStr[5];
        snprintf(noStr, sizeof(noStr), "%d.", count);
        char scoreStr[10];
        snprintf(scoreStr, sizeof(scoreStr), "%d", current->hskor);

        scale = 1.5f;
        getTextSize(noStr, scale, &width, &height);
        renderText(renderer, 400 - width / 2.0f, yPos, noStr, scale, (SDL_Color){255, 255, 255, 255}); // Aligned with header at 200
        getTextSize(current->username, scale, &width, &height);
        renderText(renderer, 650 - width / 2.0f, yPos, current->username, scale, (SDL_Color){255, 255, 255, 255}); // Aligned with header at 540
        getTextSize(scoreStr, scale, &width, &height);
        renderText(renderer, 900 - width / 2.0f, yPos, scoreStr, scale, (SDL_Color){255, 255, 255, 255}); // Aligned with header at 880

        yPos += 40;
        current = current->nextuser;
        count++;
    }

    SDL_RenderPresent(renderer);
}