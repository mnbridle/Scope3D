#include "pyramid_3.hpp"

Model pyramid_3(uint16_t id, float offset_x, float offset_y, float offset_z, float scaleFactor)
{
  Model model;
  model.id = id;

  // Add pyramid vertices
  model.vertices.push_back(Vertex3D(offset_x + -1*scaleFactor, offset_y + -0.75*scaleFactor,  offset_z + -0.75*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y + -0.75*scaleFactor,  offset_z + -0.75*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x,                  offset_y + 0.75 *scaleFactor,  offset_z + -0.75*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x,                  offset_y,                      offset_z + 0.75*scaleFactor));


  // Add pyramid edges
  model.edges.push_back(Edge(0, 1));
  model.edges.push_back(Edge(1, 2));
  model.edges.push_back(Edge(2, 0));

  model.edges.push_back(Edge(0, 3));
  model.edges.push_back(Edge(1, 3));
  model.edges.push_back(Edge(2, 3));

  return model;
}