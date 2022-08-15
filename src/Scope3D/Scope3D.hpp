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
#include "primitives/3d/teapot.hpp"
#include "primitives/2d/square.hpp"

#include "overlay/MainWindow.hpp"

using namespace std;

class Scope3D
{
    public:
        Scope3D() {
            gfx.begin(32);
            Serial.println("Done!");
        };

        // Get and set info about the projection space
        Perspective get_perspective();
        void set_perspective(Perspective perspective)
        {
            this->global_perspective = perspective;
        };

        // Get info about wireframe
        size_t get_vertices_3d_count();
        size_t get_edge_count();
        size_t get_vertices_2d_count();
        size_t get_model_count();

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

        MainWindow main_window;

        // Timing and benchmarking information
        uint64_t render_time = 0;
        uint64_t projection_time = 0;
        uint64_t display_time = 0;
        uint64_t mainwindowdraw_time = 0;
        uint64_t model_load_time = 0;
        float frame_rate = 0;
};