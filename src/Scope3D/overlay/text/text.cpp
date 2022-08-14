#include "text.hpp"

void Text::write(VectorGFX &gfx, uint16_t x, uint16_t y, char* text)
{
    gfx.moveto(x, y);
    gfx.lineto(x, y-(5*16));
    gfx.moveto(x, y-(3*16));
    gfx.lineto(x+(3*16), y-(3*16));
    gfx.lineto(x+(3*16), y-(5*16));
}
