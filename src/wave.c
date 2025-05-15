#include "fairuz.h"
#include <SDL3/SDL.h>
#include "rahma.h"

Node *head = NULL;

int waveterbaru = 1;
int bonus = 1;

void cekmusuh(Musuh *musuh)
{
    bool semuaMusuhMati = true;

    for (int i = 0; i < jumlahmusuh; i++)
    {
        if (musuh[i].aktif)
        {
            semuaMusuhMati = false;
            return;
        }
    }
    updatewave(musuh);
}

void updatewave(Musuh *musuh)
{
    if (waveterbaru < MAX_WAVE - 1)
    {
        (waveterbaru)++;

        // Tambahkan nomor wave ke dalam linked list
        addWave(&head, waveterbaru);

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

    if (bonus == 2) // Jika sedang Bonus Wave
    {
        sprintf(teksWave, "BONUS WAVE!");
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    else
    {
        // Menampilkan wave terbaru
        sprintf(teksWave, "WAVE %d", waveterbaru);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    }

    SDL_RenderDebugText(renderer, (LEBAR_LAYAR / 2) - 40, 22, teksWave);
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
