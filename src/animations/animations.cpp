#include <Arduino.h>
#include "animations.hpp"

void axes(Scope3D &scope_3d, uint16_t scale)
{
  scope_3d.clear_all();
  scope_3d.add_model(0, AXES, 0, 0, 0, scale);
}

void teapot(Scope3D &scope_3d, uint16_t scale)
{
  scope_3d.clear_all();
  scope_3d.add_model(0, TEAPOT, 0, 0, 0, scale);
  scope_3d.add_model(1, AXES, 0, 0, 0, scale);
}

void squares(Scope3D &scope_3d)
{
  scope_3d.clear_all();
  scope_3d.add_model(0, SQUARE, 0, 0, 0, 200);
  scope_3d.add_model(1, SQUARE, 400, 0, 0, 200);
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