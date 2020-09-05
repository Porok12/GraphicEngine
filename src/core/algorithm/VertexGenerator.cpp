#include <engine/core/algorithm/VertexGenerator.h>

std::vector<Vertex> VertexGenerator::generateCube(float a) {
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

std::vector<Vertex> VertexGenerator::generatePyramid(float a) {
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

Model VertexGenerator::fromVertices(const std::vector<Vertex> &vertices) {
    Mesh mesh(vertices);
    return Model(mesh);
}

void
VertexGenerator::instancedSnowflake(int n, float x, float y, float z, float d, std::vector<Vertex> &vCubes,
                                    std::vector<fVec3> &positions) {
    if (n == 0) {
        auto cube = generateCube(0);
        for (auto &v: cube) {
            v.Position *= d;
        }

        positions.emplace_back(2*x, 2*y, 2*z);
        vCubes = std::move(cube);

    } else {
        instancedSnowflake(n - 1, x + 1 * d / 3, y + 1 * d / 3, z + 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x + 1 * d / 3, y + 1 * d / 3, z - 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x + 1 * d / 3, y - 1 * d / 3, z + 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x + 1 * d / 3, y - 1 * d / 3, z - 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x - 1 * d / 3, y + 1 * d / 3, z + 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x - 1 * d / 3, y + 1 * d / 3, z - 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x - 1 * d / 3, y - 1 * d / 3, z + 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x - 1 * d / 3, y - 1 * d / 3, z - 1 * d / 3, d / 3, vCubes, positions);
        instancedSnowflake(n - 1, x, y, z, d / 3, vCubes, positions);
    }
}

void VertexGenerator::menger(int n, float x, float y, float z, float d, std::vector<std::vector<Vertex>> &vCubes) {
    if (n == 0) {
        auto cube = generateCube(0);
        for (auto &v: cube) {
            v.Position *= d;
        }

        for (auto &v: cube) {
            v.Position.x += x*2;
            v.Position.y += y*2;
            v.Position.z += z*2;
        }

        vCubes.push_back(cube);

    } else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    if ((i*i+j*j)*(i*i+k*k)*(j*j+k*k)>0) {
                        menger(n-1, x+i*d/3, y+j*d/3, z+k*d/3, d/3, vCubes);
                    }
                }
            }
        }
    }
}

void VertexGenerator::pyramid(int n, float x, float y, float z, float d, std::vector<std::vector<Vertex>> &vCubes) {
    if (n == 0) {
        auto cube = generatePyramid(0);
        for (auto &v: cube) {
            v.Position *= d;
        }

        for (auto &v: cube) {
            v.Position.x += x*2;
            v.Position.y += y*2;
            v.Position.z += z*2;
        }

        vCubes.push_back(cube);

    } else {
        pyramid(n-1, x+d/4, y, z, d/2, vCubes);
        pyramid(n-1, x+d/2, y, z+d/2, d/2, vCubes);
        pyramid(n-1, x, y, z+d/2, d/2, vCubes);
        pyramid(n-1, x+d/4, y+d/2, z+d/4, d/2, vCubes);
    }
}

void VertexGenerator::instancedMenger(int n, float x, float y, float z, float d, std::vector<Vertex> &vCubes,
                                      std::vector<fVec3> &positions) {
    if (n == 0) {
        auto cube = generateCube(d);
        for (auto &v: cube) {
            v.Position *= d;
        }

        positions.emplace_back(2*x, 2*y, 2*z);
        vCubes = std::move(cube);

    } else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    if ((i*i+j*j)*(i*i+k*k)*(j*j+k*k)>0) {
                        instancedMenger(n - 1, x + i * d / 3, y + j * d / 3, z + k * d / 3, d / 3, vCubes, positions);
                    }
                }
            }
        }
    }
}

void
VertexGenerator::instancedPyramid(int n, float x, float y, float z, float d, std::vector<Vertex> &vCubes,
                                  std::vector<fVec3> &positions) {
    if (n == 0) {
        auto pyramid = generatePyramid(d);
        positions.emplace_back(x, y, z);
        vCubes = std::move(pyramid);

    } else {
        float a = d/2;
        float hp = a * sqrt3_2;
        float h = a * sqrt6_3;
        instancedPyramid(n - 1, x + a / 2, y, z, a, vCubes, positions);
        instancedPyramid(n - 1, x, y, z - hp, a, vCubes, positions);
        instancedPyramid(n - 1, x - a / 2, y, z, a, vCubes, positions);
        instancedPyramid(n - 1, x, y + h, z - hp / 3, a, vCubes, positions);
    }
}
