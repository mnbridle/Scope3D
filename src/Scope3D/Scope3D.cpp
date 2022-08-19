#include <cmath>
#include "Scope3D.hpp"

// ---------------- OPERATIONS TO ADD PRIMITIVES ----------------
void Scope3D::add_model(uint16_t id, Primitives primitive_type, float offset_x, float offset_y, float offset_z, float scaleFactor)
{
    switch (primitive_type)
    {
        case CUBE:
            models.push_back(cube(id, offset_x, offset_y, offset_z, scaleFactor));
            break;
        case SQUARE:
            models.push_back(square(id, offset_x, offset_y, offset_z, scaleFactor));
            break;
        case PYRAMID_3:
            models.push_back(pyramid_3(id, offset_x, offset_y, offset_z, scaleFactor));
            break;
        case TEAPOT:
            models.push_back(teapot(id, offset_x, offset_y, offset_z, scaleFactor));
            break;
        case AXES:
            models.push_back(axes(id, offset_x, offset_y, offset_z, scaleFactor));
            break;
        default:
            break;
    }
}

// ---------------- GLOBAL PROJECTION AND RENDERING ----------------
void Scope3D::load_models()
{
    uint64_t start_time = esp_timer_get_time();

    // Clear 2d, 3d and edges
    clear_render();

    // Go through models, copy 3D points into global point cloud, and project them into 2D space
    // We'll save a list of VectorGFX Vertex objects

    Edge edge;
    Vertex3D vertex_3d;
    Model model;

    for (auto it = begin(models); it != end(models); ++it) {
        size_t offset = vertices_3d.size();
        model = *it;

        // Copy all 3d vertices in model into point cloud
        vertices_3d.insert(vertices_3d.end(), model.vertices.begin(), model.vertices.end());

        // Copy all edges, then modify them to point at the global-space offsets of the points in the point cloud
        size_t start = edges.size();
        edges.insert(edges.end(), model.edges.begin(), model.edges.end());
        size_t end = edges.size();

        for (auto idx = start; idx < end; ++idx)
        {
            edges[idx] += offset;
        }
    }

    uint64_t end_time = esp_timer_get_time();
    model_load_time = end_time - start_time;
}

void Scope3D::project()
{
    uint64_t start_time = esp_timer_get_time();

    // Rotate all points according to the global_perspective
    Vertex3D vertex_3d;
    clear_2d();

    for (auto it = begin(vertices_3d); it != end(vertices_3d); ++it)
    {
        vertex_3d = *it;
        vertex_3d = rotate_point(vertex_3d, global_perspective.angleX, true, false, false);
        vertex_3d = rotate_point(vertex_3d, global_perspective.angleY, false, true, false);
        vertex_3d = rotate_point(vertex_3d, global_perspective.angleZ, false, false, true);

        vertices_2d.push_back(project_point(vertex_3d));
    }

    uint64_t end_time = esp_timer_get_time();
    projection_time = end_time - start_time;

}

Vertex Scope3D::project_point(Vertex3D vertex_3d)
{
    // Do some basic projection
    float x = vertex_3d.x + (vertex_3d.z*0.3) + 2048;
    float y = vertex_3d.y + (vertex_3d.z*0.3) + 2048;

    Vertex point_2d;
    point_2d.x = static_cast<uint16_t>(x);
    point_2d.y = static_cast<uint16_t>(y);
    point_2d.bright = 255;

    return point_2d;
}

void Scope3D::render()
{
    uint64_t start_time = esp_timer_get_time();

    Edge edge;

    // Get starting coordinate
    Vertex from = vertices_2d[edges[0].from];
    Vertex to;

    Vertex3D from_3d;
    Vertex3D to_3d;

    gfx.moveto(static_cast<uint16_t>(from.x), static_cast<uint16_t>(from.y));

    // Iterate through all the edges, find the corresponding points, then draw them
    for (auto it = begin(edges); it != end(edges); ++it)
    {
        edge = *it;
        from = vertices_2d[edge.from];        
        to = vertices_2d[edge.to];

        from_3d = vertices_3d[edge.from];
        to_3d = vertices_3d[edge.to];

        gfx.moveto(static_cast<uint16_t>(from.x), static_cast<uint16_t>(from.y));
        gfx.lineto(static_cast<uint16_t>(to.x), static_cast<uint16_t>(to.y));
    }

    uint64_t end_time = esp_timer_get_time();
    render_time = end_time - start_time;

    // Call overlay
    // main_window.draw(gfx);
    main_window.show_stats(gfx, frame_rate, get_model_count(), get_vertices_2d_count(), get_edge_count());
    display();

    frame_rate = 1000000.0/(mainwindowdraw_time + model_load_time + display_time + projection_time + render_time);
}

void Scope3D::display()
{
    uint64_t start_time = esp_timer_get_time();
    gfx.display();
    uint64_t end_time = esp_timer_get_time();
    display_time = end_time - start_time;
}

// ---------------- MANIPULATE 3D VERTICES ----------------
Vertex3D Scope3D::rotate_point(Vertex3D vertex_3d, float angle, bool rotate_x, bool rotate_y, bool rotate_z)
{
    // Rotate x, then y, then z based on angles in perspective
    float x, y, z;

    float cosang = cos(radians(angle));
    float sinang = sin(radians(angle));

    x += (cosang+(1-cosang)*rotate_x*rotate_x)*vertex_3d.x;
    x += ((1-cosang)*rotate_x*rotate_y-rotate_z*sinang)*vertex_3d.y;
    x += ((1-cosang)*rotate_x*rotate_z+rotate_y*sinang)*vertex_3d.z;

    y += ((1-cosang)*rotate_x*rotate_y+rotate_z*sinang)*vertex_3d.x;
	y += (cosang+(1-cosang)*rotate_y*rotate_y)*vertex_3d.y;
	y += ((1-cosang)*rotate_y*rotate_z-rotate_x*sinang)*vertex_3d.z;

	z += ((1-cosang)*rotate_x*rotate_z-rotate_y*sinang)*vertex_3d.x;
	z += ((1-cosang)*rotate_y*rotate_z+rotate_x*sinang)*vertex_3d.y;
	z += (cosang+(1-cosang)*rotate_z*rotate_z)*vertex_3d.z;

    vertex_3d.x = x;
    vertex_3d.y = y;
    vertex_3d.z = z;

    return vertex_3d;
}

// ---------------- CLEAR DATA FROM SPACE ----------------

void Scope3D::clear_2d()
{
    vertices_2d.clear();
}

void Scope3D::clear_3d()
{
    vertices_3d.clear();
}

void Scope3D::clear_edges()
{
    edges.clear();
}

void Scope3D::clear_models()
{
    models.clear();
}

void Scope3D::clear_render()
{
    clear_2d();
    clear_3d();
    clear_edges();
}

void Scope3D::clear_all()
{
    clear_render();
    clear_models();
}

// Operations to add vertices and edges

bool Scope3D::add_vertex_3d(Vertex3D vertex_3d)
{
    vertices_3d.push_back(vertex_3d);
    return true;
}

bool Scope3D::add_edge(Edge edge)
{
    edges.push_back(edge);
    return true;
}

// Get information about the 3d space

size_t Scope3D::get_vertices_2d_count()
{
    return vertices_2d.size();
}

size_t Scope3D::get_vertices_3d_count()
{
    return vertices_3d.size();
}

size_t Scope3D::get_edge_count()
{
    return edges.size();
}

size_t Scope3D::get_model_count()
{
    return models.size();
}