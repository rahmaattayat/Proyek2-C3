#include "gema.h"
#include <stdlib.h>

Bintang bikinBintang(float x, float y, float ukuran, float kecepatan)
{
    Bintang s;
    s.x = x;
    s.y = y;
    s.ukuranBintang = ukuran;
    s.kecepatanBintang = kecepatan;
    return s;
}
