#include <engine/core/algorithm/carpet/CreateEngine.h>

std::vector<Vertex> ModelGenerator::generateCube() {
    vertices.clear();

    std::vector<fVec3> positions;
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

std::vector<Vertex> ModelGenerator::generatePyramid() {
    vertices.clear();

    std::vector<fVec3> positions;

    positions.emplace_back( 0.0f, 1.f, 0.0f );
    positions.emplace_back( -1.0f, -1.0f, 1.0f );
    positions.emplace_back( 1.0f, -1.0f, 1.0f);

    positions.emplace_back( 0.0f, 1.0f, 0.0f);
    positions.emplace_back( 0.0f, -1.0f, -1.0f);
    positions.emplace_back( -1.0f, -1.0f, 1.0f);

    positions.emplace_back( 0.0f, 1.0f, 0.0f);
    positions.emplace_back( 1.0f, -1.0f, 1.0f);
    positions.emplace_back( 0.0f, -1.0f, -1.0f);

    positions.emplace_back( -1.0f, -1.0f, 1.0f);
    positions.emplace_back( 0.0f, -1.0f, -1.0f);
    positions.emplace_back( 1.0f, -1.0f, 1.0f);

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
