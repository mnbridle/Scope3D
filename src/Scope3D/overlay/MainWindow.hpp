#include <Arduino.h>
#include <VectorGFX.h>

#include "text/text.hpp"

using namespace std;

class MainWindow
{
    public:
        MainWindow() {};
        ~MainWindow() {};

        uint64_t draw(VectorGFX &gfx);
        void show_framerate(VectorGFX &gfx);

    private:
        Text text;
};