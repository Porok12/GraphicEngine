#include <engine/core/algorithm/carpet/CreateEngine.h>

std::vector<Vertex> ModelGenerator::generateCube(float a) {
    vertices.clear();
    positions.clear();

    positions.emplace_back(-1.0f,-1.0f,-1.0f);
    positions.emplace_back(-1.0f,-1.0f, 1.0f);
    positions.emplace_back(-1.0f, 1.0f, 1.0f);
    positions.emplace_back(1.0f, 1.0f,-1.0f);
    positions.emplace_back(-1.0f,-1.0f,-1.0f);
    positions.emplace_back(-1.0f, 1.0f,-1.0f);
    positions.emplace_back(1.0f,-1.0f, 1.0f);
    positions.emplace_back(-1.0f,-1.0f,-1.0f);
    positions.emplace_back(1.0f,-1.0f,-1.0f);
    positions.emplace_back(1.0f, 1.0f,-1.0f);
    positions.emplace_back(1.0f,-1.0f,-1.0f);
    positions.emplace_back(-1.0f,-1.0f,-1.0f);
    positions.emplace_back(-1.0f,-1.0f,-1.0f);
    positions.emplace_back(-1.0f, 1.0f, 1.0f);
    positions.emplace_back(-1.0f, 1.0f,-1.0f);
    positions.emplace_back(1.0f,-1.0f, 1.0f);
    positions.emplace_back(-1.0f,-1.0f, 1.0f);
    positions.emplace_back(-1.0f,-1.0f,-1.0f);
    positions.emplace_back(-1.0f, 1.0f, 1.0f);
    positions.emplace_back(-1.0f,-1.0f, 1.0f);
    positions.emplace_back(1.0f,-1.0f, 1.0f);
    positions.emplace_back(1.0f, 1.0f, 1.0f);
    positions.emplace_back(1.0f,-1.0f,-1.0f);
    positions.emplace_back(1.0f, 1.0f,-1.0f);
    positions.emplace_back(1.0f,-1.0f,-1.0f);
    positions.emplace_back(1.0f, 1.0f, 1.0f);
    positions.emplace_back(1.0f,-1.0f, 1.0f);
    positions.emplace_back(1.0f, 1.0f, 1.0f);
    positions.emplace_back(1.0f, 1.0f,-1.0f);
    positions.emplace_back(-1.0f, 1.0f,-1.0f);
    positions.emplace_back(1.0f, 1.0f, 1.0f);
    positions.emplace_back(-1.0f, 1.0f,-1.0f);
    positions.emplace_back(-1.0f, 1.0f, 1.0f);
    positions.emplace_back(1.0f, 1.0f, 1.0f);
    positions.emplace_back(-1.0f, 1.0f, 1.0f);
    positions.emplace_back(1.0f,-1.0f, 1.0f);

    Vertex v;
    for (const auto &p: positions) {
        v.Position = p;
        v.TexCoords = fVec2(0);
        v.Normal  = fVec3(0);;
        vertices.push_back(v);
    }

    return vertices;
}

std::vector<Vertex> ModelGenerator::generatePyramid(float a) {
    vertices.clear();
    positions.clear();

    float hp = a * sqrt3_2;
    float h = a * sqrt6_3;
    fVec3 left(-a/2, -1.0f, 1.0f),
          right(a/2, -1.0f, 1.0f),
          back(0.0f, -1.0f, 1.0f - hp),
          top(0.0f, -1.0f+h, 1.0f - hp/3);

    positions.emplace_back( top.x, top.y, top.z );
    positions.emplace_back( left.x, left.y, left.z );
    positions.emplace_back( right.x, right.y, right.z);

    positions.emplace_back( top.x, top.y, top.z);
    positions.emplace_back( back.x, back.y, back.z);
    positions.emplace_back( left.x, left.y, left.z);

    positions.emplace_back( top.x, top.y, top.z);
    positions.emplace_back( right.x, right.y, right.z);
    positions.emplace_back( back.x, back.y, back.z);

    positions.emplace_back( left.x, left.y, left.z);
    positions.emplace_back( back.x, back.y, back.z);
    positions.emplace_back( right.x, right.y, right.z);

    Vertex v;
    for (const auto &p: positions) {
        v.Position = p;
        v.TexCoords = fVec2(0);
        v.Normal  = fVec3(0);;
        vertices.push_back(v);
    }

    return vertices;
}

Model ModelGenerator::fromVertices(const std::vector<Vertex> &vertices) {
    Mesh mesh(vertices);
    return Model(mesh);
}
