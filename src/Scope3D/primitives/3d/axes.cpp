#include "axes.hpp"

Model axes(uint16_t id, float offset_x, float offset_y, float offset_z, float scaleFactor)
{
  Model model;
  model.id = id;

  float arrow_size = 0.05;

  // Create unit square axis
  model.vertices.push_back(Vertex3D(offset_x, offset_y, offset_z));
  model.vertices.push_back(Vertex3D(offset_x + 1*scaleFactor,  offset_y,  offset_z));
  model.vertices.push_back(Vertex3D(offset_x,  offset_y + 1*scaleFactor,  offset_z));
  model.vertices.push_back(Vertex3D(offset_x,  offset_y,  offset_z + 1*scaleFactor));

  // Add arrows to end of each axis
  model.vertices.push_back(Vertex3D(offset_x + (1-arrow_size)*scaleFactor, offset_y - arrow_size*scaleFactor, offset_z));
  model.vertices.push_back(Vertex3D(offset_x + (1-arrow_size)*scaleFactor, offset_y + arrow_size*scaleFactor, offset_z));

  model.vertices.push_back(Vertex3D(offset_x - arrow_size*scaleFactor, offset_y + (1-arrow_size)*scaleFactor, offset_z));
  model.vertices.push_back(Vertex3D(offset_x + arrow_size*scaleFactor, offset_y + (1-arrow_size)*scaleFactor, offset_z));

  model.vertices.push_back(Vertex3D(offset_x - arrow_size*scaleFactor, offset_y, offset_z + (1-arrow_size)*scaleFactor));
  model.vertices.push_back(Vertex3D(offset_x + arrow_size*scaleFactor, offset_y, offset_z + (1-arrow_size)*scaleFactor));

  model.edges.push_back(Edge(0, 1));
  model.edges.push_back(Edge(0, 2));
  model.edges.push_back(Edge(0, 3));

  model.edges.push_back(Edge(1, 4));
  model.edges.push_back(Edge(1, 5));

  model.edges.push_back(Edge(2, 6));
  model.edges.push_back(Edge(2, 7));

  model.edges.push_back(Edge(3, 8));
  model.edges.push_back(Edge(3, 9));

  return model;
}