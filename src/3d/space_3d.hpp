#include <Arduino.h>
#include <VectorGFX.h>

#include <vector>

#define MAX_VERTICES 1024
#define MAX_EDGES 1024

using namespace std;

typedef struct Point3D
{
    float x;
    float y;
    float z;
};

typedef struct Edge
{
    uint16_t from;
    uint16_t to;
};

typedef struct Projection
{
    uint16_t width = 4096;
    uint16_t height = 4096;
    float fov = 90;
    float distance = 1500;
};

typedef struct Perspective
{
    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
};

class Space3D
{
    public:
        Space3D() {
        };
        Space3D(Projection projection, Perspective perspective)
        {
            this->projection = projection;
            this->perspective = perspective;
        };

        // Get and set info about the projection space
        Perspective get_perspective();
        Projection get_projection();

        void set_projection(Projection projection)
        {
            this->projection = projection;
        };

        void set_perspective(Perspective perspective)
        {
            this->perspective = perspective;
        };

        // Operate on points
        void clear();
        void clear_2d();
        bool add_point(Point3D);
        bool add_edge(Edge);

        // Get info about wireframe
        uint16_t get_vertices_count();
        uint16_t get_edge_count();
        uint16_t get_rendered_points_count();

        // Render operations
        void project();
        void render(VectorGFX& gfx);

    private:
        Projection projection;
        Perspective perspective;

        vector<Point3D> points_3d;
        vector<Vertex> vertices;
        vector<Edge> edges;

        Point3D rotate_point(Point3D, float angle, bool rotate_x, bool rotate_y, bool rotate_z);
        Vertex project_point(Point3D point);
};