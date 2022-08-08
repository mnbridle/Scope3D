#include <Arduino.h>
#include <vector>

#include <VectorGFX.h>

#ifndef COMMON_H
#define COMMON_H
#include "common.hpp"
#endif

#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include "primitives/primitives.hpp"
#endif

#include "primitives/3d/cube.hpp"
#include "primitives/3d/pyramid_3.hpp"

#include "primitives/2d/square.hpp"

using namespace std;

class Space3D
{
    public:
        Space3D() {
            gfx.begin();
            Serial.println("Done!");
        };

        // Get and set info about the projection space
        Perspective get_perspective();
        void set_perspective(Perspective perspective)
        {
            this->global_perspective = perspective;
        };

        // Get info about wireframe
        uint16_t get_vertices_3d_count();
        uint16_t get_edge_count();
        uint16_t get_vertices_2d_count();

        // Add shape or volume
        void add_model(uint16_t id, Primitives primitive_type, float offset_x, float offset_y, float offset_z, float scaleFactor);

        void clear_2d();
        void clear_3d();
        void clear_edges();
        void clear_models();
        void clear_render();
        void clear_all();

        // Render operations
        void load_models();
        void project();
        void render();
        void display();

    private:
        // Set global perspective
        Perspective global_perspective;

        // All graphics primitives are first added to models vector
        vector<Model> models;

        // All vertices from all models are added to a point cloud
        vector<Vertex3D> vertices_3d;
        vector<Vertex> vertices_2d;
        vector<Edge> edges;

        // Display output
        VectorGFX gfx;

        // Add points and edges to the point cloud
        bool add_vertex_3d(Vertex3D);
        bool add_edge(Edge);

        Vertex3D rotate_point(Vertex3D, float angle, bool rotate_x, bool rotate_y, bool rotate_z);
        Vertex project_point(Vertex3D point);
};