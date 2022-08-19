#include "MainWindow.hpp"

uint64_t MainWindow::draw(VectorGFX &gfx) {
    uint64_t start = esp_timer_get_time();
    gfx.moveto(0, 0);
    gfx.lineto(0, 4095);
    gfx.lineto(4095, 4095);
    gfx.lineto(4095, 0);
    gfx.lineto(0, 0);

    // Top of stats bar
    gfx.moveto(0, 256);
    gfx.lineto(4095, 256);

    return esp_timer_get_time() - start;
}

void MainWindow::show_stats(VectorGFX &gfx, float frame_rate, size_t model_count, size_t vertex_count, size_t edge_count) {
    char buf[100];
    int buf_len = snprintf(buf, sizeof(buf), "m: %i, v: %i, e: %i, %6.1f fps", model_count, vertex_count, edge_count, frame_rate);
    text.write(gfx, 32, 48, 6, buf, buf_len);
}