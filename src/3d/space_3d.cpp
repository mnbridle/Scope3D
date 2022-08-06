#include "space_3d.hpp"
#include <cmath>

void Space3D::project()
{
    // First, clear old 2d vertices
    vertices.clear();

    // Go through list of 3D points, and project them into 2D space
    // We'll save a list of VectorGFX Vertex objects
    Point3D point;

    for (auto it = begin(points_3d); it != end(points_3d); ++it)
    {
        point = *it;
        point = rotate_point(point, perspective.angleX, true, false, false);
        point = rotate_point(point, perspective.angleY, false, true, false);
        point = rotate_point(point, perspective.angleZ, false, false, true);

        vertices.push_back(project_point(point));
    }
}

void Space3D::render(VectorGFX& gfx)
{
    Edge edge;

    // Get starting coordinate
    Vertex from = vertices[edges[0].from];
    Vertex to;

    Point3D from_3d;
    Point3D to_3d;

    gfx.moveto(static_cast<uint16_t>(from.x), static_cast<uint16_t>(from.y));

    // Iterate through all the edges, find the corresponding points, then draw them
    for (auto it = begin(edges); it != end(edges); ++it)
    {
        edge = *it;
        from = vertices[edge.from];        
        to = vertices[edge.to];

        from_3d = points_3d[edge.from];
        to_3d = points_3d[edge.to];

        gfx.moveto(static_cast<uint16_t>(from.x), static_cast<uint16_t>(from.y));
        gfx.lineto(static_cast<uint16_t>(to.x), static_cast<uint16_t>(to.y));
    }

    gfx.moveto(0, 0);
    gfx.lineto(0, 4096);
    gfx.lineto(4096, 4096);
    gfx.lineto(4096, 0);
    gfx.lineto(0, 0);

    gfx.display();
}

bool Space3D::add_point(Point3D point)
{
    points_3d.push_back(point);
    return true;
}

bool Space3D::add_edge(Edge edge)
{
    edges.push_back(edge);
    return true;
}

Point3D Space3D::rotate_point(Point3D point, float angle, bool rotate_x, bool rotate_y, bool rotate_z)
{
    // Rotate x, then y, then z based on angles in perspective
    float x, y, z;

    float cosang = cos(radians(angle));
    float sinang = sin(radians(angle));

    x += (cosang+(1-cosang)*rotate_x*rotate_x)*point.x;
    x += ((1-cosang)*rotate_x*rotate_y-rotate_z*sinang)*point.y;
    x += ((1-cosang)*rotate_x*rotate_z+rotate_y*sinang)*point.z;

    y += ((1-cosang)*rotate_x*rotate_y+rotate_z*sinang)*point.x;
	y += (cosang+(1-cosang)*rotate_y*rotate_y)*point.y;
	y += ((1-cosang)*rotate_y*rotate_z-rotate_x*sinang)*point.z;

	z += ((1-cosang)*rotate_x*rotate_z-rotate_y*sinang)*point.x;
	z += ((1-cosang)*rotate_y*rotate_z+rotate_x*sinang)*point.y;
	z += (cosang+(1-cosang)*rotate_z*rotate_z)*point.z;

    point.x = x;
    point.y = y;
    point.z = z;

    return point;
}

Vertex Space3D::project_point(Point3D point)
{
    // Do some basic projection
    float x = point.x + (point.z*0.3) + projection.width/2;
    float y = point.y + (point.z*0.3) + projection.height/2;

    Vertex point_2d;
    point_2d.x = static_cast<uint16_t>(x);
    point_2d.y = static_cast<uint16_t>(y);
    point_2d.bright = 255;

    return point_2d;
}

void Space3D::clear()
{
    vertices.clear();
    edges.clear();
    points_3d.clear();
}

void Space3D::clear_2d()
{
    vertices.clear();
}

uint16_t Space3D::get_rendered_points_count()
{
    return vertices.size();
}

uint16_t Space3D::get_edge_count()
{
    return edges.size();
}

uint16_t Space3D::get_vertices_count()
{
    return points_3d.size();
}