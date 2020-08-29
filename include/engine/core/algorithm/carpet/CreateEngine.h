#ifndef XXX_H
#define XXX_H

#include <engine/math/Vec3.h>
#include <engine/core/models/Model.h>

class ModelGenerator {
private:
    std::vector<Vertex> vertices;
public:
    std::vector<Vertex> generateCube();
    std::vector<Vertex> generatePyramid();
    Model fromVertices(const std::vector<Vertex> &vertices);

    void menger(int n, float x, float y, float z, float d, vector<vector<Vertex>> &vCubes) {
        if (n == 0) {
            auto cube = generateCube();
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

    void pyramid(int n, float x, float y, float z, float d, vector<vector<Vertex>> &vCubes) {
        if (n == 0) {
            auto cube = generatePyramid();
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
};

#endif // XXX_H
