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
        void show_stats(VectorGFX &gfx, float frame_rate, size_t model_count, size_t vertex_count, size_t edge_count);

    private:
        Text text;
};