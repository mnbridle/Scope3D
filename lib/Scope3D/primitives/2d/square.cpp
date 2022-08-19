#include "square.hpp"

Model square(uint16_t id, float offset_x, float offset_y, float offset_z, float scaleFactor)
{
  Model model;
  model.id = id;

  // Add cube vertices
  model.vertices.push_back(Vertex3D(offset_x + -1*scaleFactor, offset_y + 1*scaleFactor,  offset_z + 0));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y + 1*scaleFactor,  offset_z + 0));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y + -1*scaleFactor, offset_z + 0));
  model.vertices.push_back(Vertex3D(offset_x + -1*scaleFactor, offset_y + -1*scaleFactor, offset_z + 0));

  // Add cube edges
  model.edges.push_back(Edge(0, 1));
  model.edges.push_back(Edge(1, 2));
  model.edges.push_back(Edge(2, 3));
  model.edges.push_back(Edge(3, 0));

  return model;
}