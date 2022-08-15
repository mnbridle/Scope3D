#include "teapot.hpp"

Model teapot(uint16_t id, float offset_x, float offset_y, float offset_z, float scaleFactor)
{
    Vertex3D vertex3d;
    Edge edge;

    uint16_t bezier_patch[16];

    Model model;
    model.id = id;

    for (int i=0; i<vertex_count; i++) {
        vertex3d = teapot_vertices[i];
        vertex3d.x *= scaleFactor;
        vertex3d.y *= scaleFactor;
        vertex3d.z *= scaleFactor;

        vertex3d.x += offset_x;
        vertex3d.y += offset_y;
        vertex3d.z += offset_z;

        model.vertices.push_back(vertex3d);
    }

    // Iterate through Bezier patches, add edge
    for (int i=0; i<32; i++)
    {
        std::copy(std::begin(bezier_patches[i]), std::end(bezier_patches[i]), std::begin(bezier_patch));
        // Edge strategy - forward and down
        for (int j=0; j<15; j++)
        {
            edge.from = bezier_patch[j];
            
            // Forward
            if (j!=3 && j!=7 && j!=11 && j!= 15)
            {
                edge.to = bezier_patch[j+1];
                model.edges.push_back(edge);
            }

            // Down
            if (j<12)
            {
                edge.to = bezier_patch[j+4];
                model.edges.push_back(edge);
            }
        }
    }

    return model;
}
