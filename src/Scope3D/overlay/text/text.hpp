#include <Arduino.h>
#include <VectorGFX.h>
#include <string>

using namespace std;

class Text {
    public:
        Text() {};
        ~Text() {};
        void write(VectorGFX &gfx, uint16_t x, uint16_t y, char *text);

    private:
};