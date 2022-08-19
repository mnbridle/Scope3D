#include "text.hpp"
#include "fonts/simplex.hpp"

void Text::write(VectorGFX &gfx, uint16_t offset_x, uint16_t offset_y, uint8_t scaling, const char* text, uint8_t text_len)
{
    uint8_t vertex_count = 0;
    uint8_t horizontal_spacing = 0;

    int x = 0;
    int y = 0;
    bool liftUpPen = false;

    for (int i=0; i<text_len; i++)
    {
        // Get character info from array
        vertex_count = simplex[text[i]-32][0];
        horizontal_spacing = simplex[text[i]-32][1];

        // Vertices are groups of 2, starting at offset (2, 3)
        for (int vertex=0; vertex<vertex_count; vertex++)
        {
            x = simplex[text[i]-32][2+vertex*2];
            y = simplex[text[i]-32][3+vertex*2];

            if (vertex==0 || liftUpPen)
            {
                gfx.moveto(offset_x + (x*scaling), offset_y + (y*scaling));
                liftUpPen = false;
            } 
            else if (x == -1 && y == -1)
            {
                // Lift up pen
                liftUpPen = true;
            }
            else
            {
                gfx.lineto(offset_x + (x*scaling), offset_y + (y*scaling));
            }
        }

        offset_x += horizontal_spacing*scaling;
    }
}
