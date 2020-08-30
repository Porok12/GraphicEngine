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

    void iMenger2(int n, float x, float y, float z, float d, vector<Vertex> &vCubes, vector<fVec3> &positions) {
        if (n == 0) {
            auto cube = generateCube();
            for (auto &v: cube) {
                v.Position *= d;
            }

            positions.emplace_back(2*x, 2*y, 2*z);
            vCubes = std::move(cube);

        } else {
            iMenger2(n-1, x+1*d/3, y+1*d/3, z+1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x+1*d/3, y+1*d/3, z-1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x+1*d/3, y-1*d/3, z+1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x+1*d/3, y-1*d/3, z-1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x-1*d/3, y+1*d/3, z+1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x-1*d/3, y+1*d/3, z-1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x-1*d/3, y-1*d/3, z+1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x-1*d/3, y-1*d/3, z-1*d/3, d/3, vCubes, positions);
            iMenger2(n-1, x, y, z, d/3, vCubes, positions);
        }
    }

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

    void iMenger(int n, float x, float y, float z, float d, vector<Vertex> &vCubes, vector<fVec3> &positions) {
        if (n == 0) {
            auto cube = generateCube();
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
                            iMenger(n-1, x+i*d/3, y+j*d/3, z+k*d/3, d/3, vCubes, positions);
                        }
                    }
                }
            }
        }
    }

    void iPyramid(int n, float x, float y, float z, float d, vector<Vertex> &vCubes, vector<fVec3> &positions) {
        if (n == 0) {
            auto cube = generatePyramid();
            for (auto &v: cube) {
                v.Position *= d;
            }

            positions.emplace_back(x, y, z);
            vCubes = std::move(cube);

        } else {
            float s3 = std::sqrt(3) / 2;
            float half = d/2;
            float h = 2*std::sqrt(half*half - (2/3 * half*s3));
            iPyramid(n-1, x+half, y, z, half, vCubes, positions);
            iPyramid(n-1, x, y, z-d*s3, half, vCubes, positions);
            iPyramid(n-1, x-half, y, z, half, vCubes, positions);
            iPyramid(n-1, x, y+h, z-half*s3*2/3, half, vCubes, positions);
        }
    }
};

#endif // XXX_H
