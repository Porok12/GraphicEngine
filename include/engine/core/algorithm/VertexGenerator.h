#ifndef VERTEX_GENERATOR_H
#define VERTEX_GENERATOR_H

#include <engine/math/Vec3.h>
#include <engine/core/models/Model.h>

class VertexGenerator {
private:
    const float sqrt3_2 = static_cast<const float>(std::sqrt(3) / 2);
    const float sqrt6_3 = static_cast<const float>(std::sqrt(6) / 3);

    std::vector<Vertex> vertices;
    std::vector<fVec3> positions;

public:
    std::vector<Vertex> generateCube(float a);
    std::vector<Vertex> generatePyramid(float a);
    Model fromVertices(const std::vector<Vertex> &vertices);

    void menger(int n, float x, float y, float z, float d, std::vector<std::vector<Vertex>> &vCubes);
    void pyramid(int n, float x, float y, float z, float d, std::vector<std::vector<Vertex>> &vCubes);
    void instancedMenger(int n, float x, float y, float z, float d, std::vector<Vertex> &vCubes, std::vector<fVec3> &positions);
    void instancedSnowflake(int n, float x, float y, float z, float d, std::vector<Vertex> &vCubes, std::vector<fVec3> &positions);
    void instancedPyramid(int n, float x, float y, float z, float d, std::vector<Vertex> &vCubes, std::vector<fVec3> &positions);
};

#endif // VERTEX_GENERATOR_H
