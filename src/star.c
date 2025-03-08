#include "gema.h"
#include <stdlib.h>

Bintang bikinBintang(float x, float y, float size, float speed)
{
    Bintang s;
    s.x = x;
    s.y = y;
    s.size = size;
    s.speed = speed;
    return s;
}
