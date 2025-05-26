#include "fairuz.h"
#include <SDL3/SDL.h>
#include "rahma.h"
#include "ihsan.h"

int waveterbaru = 1;
int bonus = 1;

void cekmusuh(Musuh *musuh)
{
    NodeMusuh *curr = headMusuh;
    bool semuaMusuhMati = true;

    while (curr)
    {
        if (curr->data.aktif)
        {
            semuaMusuhMati = false;
            return;
        }
        curr = curr->next;
    }
    updatewave(NULL);
}

void updatewave(Musuh *musuh)
{
    if (waveterbaru < MAX_WAVE - 1)
    {
        (waveterbaru)++;

        bonuswave(waveterbaru);
        jumlahmusuh = tambahmusuh(jumlahmusuh, waveterbaru);

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
    SDL_Color warnaTeksWave;

    if (bonus == 2) // Jika sedang Bonus Wave
    {
        sprintf(teksWave, "BONUS WAVE!");
        warnaTeksWave = (SDL_Color){255, 0, 0, 255};
    }
    else
    {
        sprintf(teksWave, "WAVE %d", waveterbaru);
        warnaTeksWave = (SDL_Color){255, 255, 0, 255};
    }

    renderText(renderer, (LEBAR_LAYAR / 2) - 40, 22, teksWave, 1.0f, warnaTeksWave);
}

int tambahmusuh(int jumlahmusuh, int waveterbaru)
{
    return jumlahmusuh + waveterbaru;
}

void bonuswave(int waveterbaru)
{
    if (waveterbaru % 5 == 0)
    {
        bonus = 2; // Poin dikali 2
        SDL_Log("BONUS WAVE! Semua poin digandakan!");
    }
    else
    {
        bonus = 1; // Normal wave
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
