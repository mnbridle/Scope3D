#include <Arduino.h>
#include <VectorGFX.h>

#include "3d/space_3d.hpp"

VectorGFX gfx;
Space3D space3D;

void testPattern()
{
    /* Square in bottom-left */
    gfx.moveto(0, 0);
    gfx.lineto(1024, 0);
    gfx.lineto(1024, 1024);
    gfx.lineto(0, 1024);
    gfx.lineto(0, 0);

    /* Fill square with starbust pattern */
    gfx.moveto(0, 0);
    for (unsigned j = 0; j <= 1024; j += 128)
    {

        gfx.lineto(1024, j);
        gfx.moveto(0, 0);
        gfx.lineto(j, 1024);
        gfx.moveto(0, 0);
    }
    for (unsigned j = 0; j < 1024; j += 128)
    {

        gfx.lineto(j, 1024);
        gfx.moveto(0, 0);
    }

    /* Triangle in bottom-right */
    gfx.moveto(4095, 0);
    gfx.lineto(4095 - 512, 0);
    gfx.lineto(4095 - 0, 512);
    gfx.lineto(4095, 0);

    /* Square in top-right */
    gfx.moveto(4095, 4095);
    gfx.lineto(4095 - 512, 4095);
    gfx.lineto(4095 - 512, 4095 - 512);
    gfx.lineto(4095, 4095 - 512);
    gfx.lineto(4095, 4095);

    /* Hourglass in top-left */
    gfx.moveto(0, 4095);
    gfx.lineto(512, 4095);
    gfx.lineto(0, 4095 - 512);
    gfx.lineto(512, 4095 - 512);
    gfx.lineto(0, 4095);

    /* Center target */
    gfx.moveto(2047, 2047 - 512);
    gfx.lineto(2047, 2047 + 512);
    gfx.moveto(2047 - 512, 2047);
    gfx.lineto(2047 + 512, 2047);
}

void setup() {
  Serial.begin(115200);

  Serial.println("Initialising 3D space...");
  space3D = Space3D();

  Serial.println("Starting gfx engine...");
  gfx.begin();

  Serial.println("Initialising camera perspective");

  Perspective perspective;
  Projection projection;

  space3D.set_perspective(perspective);
  space3D.set_projection(projection);

  testPattern();
  gfx.display();
  delay(5000);
}

void draw_cube(float offset_x, float offset_y, float offset_z, float scaleFactor)
{
  int point_count = space3D.get_vertices_count();
  Edge edge;

  // Load our points into there
  space3D.add_point(Point3D {.x = offset_x + -1*scaleFactor, .y = offset_y + 1*scaleFactor, .z = offset_z + -1*scaleFactor});
  space3D.add_point(Point3D {.x = offset_x + 1*scaleFactor, .y = offset_y + 1*scaleFactor, .z = offset_z + -1*scaleFactor});
  space3D.add_point(Point3D {.x = offset_x + 1*scaleFactor, .y = offset_y + -1*scaleFactor, .z = offset_z + -1*scaleFactor});
  space3D.add_point(Point3D {.x = offset_x + -1*scaleFactor, .y = offset_y + -1*scaleFactor, .z = offset_z + -1*scaleFactor});

  space3D.add_point(Point3D {.x = offset_x + -1*scaleFactor, .y = offset_y + 1*scaleFactor, .z = offset_z + 1*scaleFactor});
  space3D.add_point(Point3D {.x = offset_x + 1*scaleFactor, .y = offset_y + 1*scaleFactor, .z = offset_z + 1*scaleFactor});
  space3D.add_point(Point3D {.x = offset_x + 1*scaleFactor, .y = offset_y + -1*scaleFactor, .z = offset_z + 1*scaleFactor});
  space3D.add_point(Point3D {.x = offset_x + -1*scaleFactor, .y = offset_y + -1*scaleFactor, .z = offset_z + 1*scaleFactor});

  Serial.println("Connecting the points with edges...");
 
  edge.from = 0 + point_count;
  edge.to = 1 + point_count;
  space3D.add_edge(edge);

  edge.from = 1 + point_count;
  edge.to = 2 + point_count;
  space3D.add_edge(edge);

  edge.from = 2 + point_count;
  edge.to = 3 + point_count;
  space3D.add_edge(edge);

  edge.from = 3 + point_count;
  edge.to = 0 + point_count;
  space3D.add_edge(edge);

  // Extra cross vertices
  // edge.from = 0 + point_count;
  // edge.to = 2 + point_count;
  // space3D.add_edge(edge);

  // edge.from = 1 + point_count;
  // edge.to = 3 + point_count;
  // space3D.add_edge(edge);

  edge.from = 4 + point_count;
  edge.to = 5 + point_count;
  space3D.add_edge(edge);

  edge.from = 5 + point_count;
  edge.to = 6 + point_count;
  space3D.add_edge(edge);

  edge.from = 6 + point_count;
  edge.to = 7 + point_count;
  space3D.add_edge(edge);

  edge.from = 7 + point_count;
  edge.to = 4 + point_count;
  space3D.add_edge(edge);

  edge.from = 0 + point_count;
  edge.to = 4 + point_count;
  space3D.add_edge(edge);

  edge.from = 1 + point_count;
  edge.to = 5 + point_count;
  space3D.add_edge(edge);

  edge.from = 2 + point_count;
  edge.to = 6 + point_count;
  space3D.add_edge(edge);

  edge.from = 3 + point_count;
  edge.to = 7 + point_count;
  space3D.add_edge(edge);
}

void cube_explosion(uint16_t scale)
{
  space3D.clear();
  // Fill scene with objects
  draw_cube(0, 0, 0, 400);

  draw_cube(-1*scale, 0, 0, 200);
  draw_cube(1*scale, 0, 0, 200);
  draw_cube(0, -1*scale, 0, 200);
  draw_cube(0, 1*scale, 0, 200);
  draw_cube(0, 0, -1*scale, 200);
  draw_cube(0, 0, 1*scale, 200);
}

// ----------------------------------------------
// main loop
// ----------------------------------------------
void loop() {
  gfx.display();
  Serial.println("Adding points to the 3D space...");
  
  Perspective perspective;
  perspective.angleX = 0;
  perspective.angleY = 0;
  perspective.angleZ = 0;

  uint16_t scale = 0;

  float degrees_per_tick = 1.5;

  while (1)
  {   
    Serial.println("Set perspective and projection");

    cube_explosion(scale+=5);

    if (scale > 1500)
    {
      scale = 1500;
    }

    perspective.angleX += degrees_per_tick;
    perspective.angleY += degrees_per_tick / 10;
    perspective.angleZ += degrees_per_tick / 10;

    space3D.set_perspective(perspective);

    space3D.project();
    space3D.render(gfx);

    space3D.clear_2d();
  }

  Serial.println("Wait 1000ms before trying it all again");
  delay(1000);
  space3D.clear();
}