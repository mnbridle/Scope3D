#include "MainWindow.hpp"

uint64_t MainWindow::draw(VectorGFX &gfx) {
    uint64_t start = esp_timer_get_time();
    gfx.moveto(0, 0);
    gfx.lineto(0, 4095);
    gfx.lineto(4095, 4095);
    gfx.lineto(4095, 0);
    gfx.lineto(0, 0);

    // for (int i=0; i<32; i++)
    // {
    //     text.write(gfx, 1024 + (i*5*16), 2048, "Hello world");
    // }

    return esp_timer_get_time() - start;
}

void MainWindow::show_framerate(VectorGFX &gfx) {

}