#include <string.h>
#include "alda.h"
#include "gema.h"

char currentUsername[50] = "";

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

void sortLeaderboard() {
    if (headuser == NULL || headuser->nextuser == NULL) return;

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