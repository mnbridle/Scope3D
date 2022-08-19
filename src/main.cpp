#include <Arduino.h>

#define SCOPE3D_H
#include "Scope3D/Scope3D.hpp"

#include "animations/animations.hpp"

Scope3D scope_3d;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 3D Wireframe");
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

  // Show a rotating axes for 30 seconds
  start_time = esp_timer_get_time();
  scale = 1600;
  scale_per_tick = 2.5;
  degrees_per_tick = 1.5;

  while (esp_timer_get_time() - start_time < 30*1000000)
  {
    axes(scope_3d, scale);
    scope_3d.load_models();

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