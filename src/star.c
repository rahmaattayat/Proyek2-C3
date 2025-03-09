#include "gema.h"
#include <stdlib.h>

Bintang bikinBintang(float x, float y, float size, float speed)
{
    Bintang s;
    s.x = x;
    s.y = y;
    s.ukuranBintang = size;
    s.kecepatanBintang = speed;
    return s;
}
