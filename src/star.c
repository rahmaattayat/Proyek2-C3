#include "gema.h"
#include <stdlib.h>

Star create_star(float x, float y, float size, float speed) {
    Star s;
    s.x = x;
    s.y = y;
    s.size = size;
    s.speed = speed;
    return s;
}
