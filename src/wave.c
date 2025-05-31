#include "fairuz.h"
#include <SDL3/SDL.h>
#include "rahma.h"
#include "ihsan.h"
#include <stdlib.h>

int bonus = 1;
Node *headWave = NULL;

int getLastWaveNumber(Node *head)
{
    if (head == NULL)
        return 0;
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp->waveNumber;
}

void cekmusuh(Musuh *musuh)
{
    NodeMusuh* curr = headMusuh;
    bool semuaMusuhMati = true;

    while (curr){
        if (curr->data.aktif){
            semuaMusuhMati = false;
            return;
        }
        curr = curr->next;
    }
    updatewave(musuh);
}

void updatewave(Musuh *musuh)
{
    int lastWave = getLastWaveNumber(headWave);

    if (lastWave < MAX_WAVE - 1)
    {
        int newWave = lastWave + 1;
        addWave(&headWave, newWave);

        bonuswave(newWave);
        jumlahmusuh = tambahmusuh (jumlahmusuh, newWave);

        if (jumlahmusuh > MAX_MUSUH)
        {
            jumlahmusuh = MAX_MUSUH;
        }
        SDL_Log("jumlah musuh = %d", jumlahmusuh);
        bikinMusuh(musuh, jumlahmusuh, 1);
    }
}

void tampilkanWave(SDL_Renderer *renderer)
{
    char teksWave[20];
    int currentWave = getLastWaveNumber(headWave);
    SDL_Color warnaTeksWave;

    if (bonus == 2)
    {
        sprintf(teksWave, "BONUS WAVE!");
        warnaTeksWave = (SDL_Color){255, 0, 0, 255};
    }
    else
    {
        sprintf(teksWave, "WAVE %d", currentWave);
        warnaTeksWave = (SDL_Color){255, 255, 0, 255};
    }

    renderText(renderer, (LEBAR_LAYAR / 2) - 40, 22, teksWave, 1.0f, warnaTeksWave);
}

int tambahmusuh(int jumlahmusuh, int waveNumber)
{
    return jumlahmusuh + 2;
}

void bonuswave(int waveNumber)
{
    if (waveNumber % 5 == 0)
    {
        bonus = 2;
        SDL_Log("BONUS WAVE! Semua poin digandakan!");
    }
    else
    {
        bonus = 1;
    }
}

// Fungsi untuk menambah node baru ke linked list
void addWave(Node **head, int waveNumber)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->waveNumber = waveNumber;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void freeWaves(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }

    // Setelah semua node dihapus, set pointer global ke NULL
    headWave = NULL;
}
