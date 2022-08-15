#include <Arduino.h>
#include "Scope3D/Scope3D.hpp"

Scope3D scope_3d;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 3D Wireframe");
}

void cube_explosion(Scope3D &scope_3d, uint16_t scale)
{
  scope_3d.clear_all();
  // Fill scene with objects
  scope_3d.add_model(0, CUBE,  0,        0,       0,       400);
  scope_3d.add_model(1, CUBE, -1*scale,  0,       0,       200);
  scope_3d.add_model(2, CUBE,  1*scale,  0,       0,       200);
  scope_3d.add_model(3, CUBE,  0,       -1*scale, 0,       200);
  scope_3d.add_model(4, CUBE,  0,        1*scale, 0,       200);
  scope_3d.add_model(5, CUBE,  0,        0,      -1*scale, 200);
  scope_3d.add_model(6, CUBE,  0,        0,       1*scale, 200);

  scope_3d.add_model(7, PYRAMID_3, -1*scale, -1*scale, 0, 200);
  scope_3d.add_model(8, PYRAMID_3,  1*scale,  1*scale, 0, 200);
  scope_3d.add_model(9, PYRAMID_3, -1*scale,  1*scale, 0, 200);
  scope_3d.add_model(10, PYRAMID_3, 1*scale, -1*scale, 0, 200);

  scope_3d.add_model(11, PYRAMID_3, -1*scale, -1*scale, -1*scale, 200);
  scope_3d.add_model(12, PYRAMID_3,  1*scale,  1*scale, -1*scale, 200);
  scope_3d.add_model(13, PYRAMID_3, -1*scale,  1*scale, -1*scale, 200);
  scope_3d.add_model(14, PYRAMID_3,  1*scale, -1*scale, -1*scale, 200);

  scope_3d.add_model(15, PYRAMID_3, -1*scale, -1*scale, 1*scale, 200);
  scope_3d.add_model(16, PYRAMID_3,  1*scale,  1*scale, 1*scale, 200);
  scope_3d.add_model(17, PYRAMID_3, -1*scale,  1*scale, 1*scale, 200);
  scope_3d.add_model(18, PYRAMID_3,  1*scale, -1*scale, 1*scale, 200);
}

void squares(Scope3D &scope_3d)
{
  scope_3d.clear_all();
  scope_3d.add_model(0, SQUARE, 0, 0, 0, 200);
  scope_3d.add_model(1, SQUARE, 400, 0, 0, 200);
}

void teapot(Scope3D &scope_3d, uint16_t scale)
{
  scope_3d.clear_all();
  scope_3d.add_model(0, TEAPOT, 0, 0, 0, scale);
}

void loop() {
  Perspective perspective;
  perspective.angleX = 0;
  perspective.angleY = 0;
  perspective.angleZ = 0;
  scope_3d.set_perspective(perspective);
  scope_3d.display();

  // Run first example for 30 seconds
  uint64_t start_time = esp_timer_get_time();
  uint16_t scale = 0;
  uint16_t scale_per_tick = 2.5;
  float degrees_per_tick = 1.5;

  while (esp_timer_get_time() - start_time < 10*1000000)
  {
    cube_explosion(scope_3d, scale);
    scope_3d.load_models();

    scale += scale_per_tick;
    if(scale>800)
    {
      scale = 800;
    }

    perspective.angleX += degrees_per_tick;
    perspective.angleY += degrees_per_tick / 10;
    perspective.angleZ += degrees_per_tick / 10;

    scope_3d.set_perspective(perspective);
    scope_3d.project();
    scope_3d.render();
  }

  // Show the teapot
  scale = 300;
  teapot(scope_3d, scale);
  scope_3d.load_models();

  while (1)
  {
    perspective.angleX += degrees_per_tick;
    perspective.angleY += degrees_per_tick / 10;
    perspective.angleZ += degrees_per_tick / 10;

    scope_3d.set_perspective(perspective);
    scope_3d.project();
    scope_3d.render();
  }
}