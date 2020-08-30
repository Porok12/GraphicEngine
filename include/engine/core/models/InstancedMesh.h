#ifndef INSTANCED_MESH_H
#define INSTANCED_MESH_H

#include <vector>
#include <engine/math/Vec3.h>
#include "Mesh.h"

class InstancedMesh {
private:
    std::vector<fVec3> positions;
    std::vector<Vertex> vertices;
    GLuint VAO;
    GLuint buffer[2];
public:
//    InstancedMesh() = default;
//    explicit InstancedMesh(std::vector<Vertex> &vertices);
    void loadMesh(vector<Vertex> vertices);
    void setPositions(std::vector<fVec3> positions);
    void draw(std::vector<fVec3> &positions) const;
    void draw() const;
};

#endif // INSTANCED_MESH_H