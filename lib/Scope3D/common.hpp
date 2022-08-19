#include <Arduino.h>
#include <vector>

using namespace std;

struct Vertex3D
{
    // default + parameterized constructor
    Vertex3D(float x=0, float y=0, float z=0) 
        : x(x), y(y), z(z)
    {
    }
    float x;
    float y;
    float z;
};

struct Edge
{
    uint16_t from;
    uint16_t to;

    // default + parameterized constructor
    Edge(uint16_t from=0, uint16_t to=0) 
        : from(from), to(to)
    {
    }

    Edge& operator+=(const size_t offset)
    {
        this->from += offset;
        this->to += offset;
        return *this;
    }
};

struct Perspective
{
    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
};

// Combine all three of these
struct Model
{
    uint16_t id;
    Perspective perspective;
    vector<Vertex3D> vertices;
    vector<Edge> edges;
};