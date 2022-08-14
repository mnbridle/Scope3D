#include "cube.hpp"

Model cube(uint16_t id, float offset_x, float offset_y, float offset_z, float scaleFactor)
{
  Model model;
  model.id = id;

  // Add cube vertices
  model.vertices.push_back(Vertex3D(offset_x + -1*scaleFactor, offset_y + 1*scaleFactor,  offset_z + -1*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y + 1*scaleFactor,  offset_z + -1*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y + -1*scaleFactor, offset_z + -1*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + -1*scaleFactor, offset_y + -1*scaleFactor, offset_z + -1*scaleFactor));

  model.vertices.push_back(Vertex3D(offset_x + -1*scaleFactor, offset_y + 1*scaleFactor,  offset_z + 1*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y + 1*scaleFactor,  offset_z + 1*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y + -1*scaleFactor, offset_z + 1*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + -1*scaleFactor, offset_y + -1*scaleFactor, offset_z + 1*scaleFactor));

  // Add cube edges
  model.edges.push_back(Edge(0, 1));
  model.edges.push_back(Edge(1, 2));
  model.edges.push_back(Edge(2, 3));
  model.edges.push_back(Edge(3, 0));

  model.edges.push_back(Edge(4, 5));
  model.edges.push_back(Edge(5, 6));
  model.edges.push_back(Edge(6, 7));
  model.edges.push_back(Edge(7, 4));
  
  model.edges.push_back(Edge(0, 4));
  model.edges.push_back(Edge(1, 5));
  model.edges.push_back(Edge(2, 6));
  model.edges.push_back(Edge(3, 7));

  return model;
}