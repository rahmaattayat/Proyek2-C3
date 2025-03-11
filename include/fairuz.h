#ifndef FAIRUZ_H
#define FAIRUZ_H

#include "rahma.h"
#include "alda.h"
#include "gema.h"
#include "ihsan.h"
#include "config.h"

#define MAX_MUSUH 50
#define MAX_WAVE 10

typedef struct
{
    int wave;
} Wave;

/// k
extern int waveterbaru;
extern int jumlahmusuh;

void updatewave(Musuh *musuh);
void cekmusuh(Musuh musuh[]);

#endif
