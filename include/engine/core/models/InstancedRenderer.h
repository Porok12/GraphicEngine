#ifndef INSTANCED_RENDERER_H
#define INSTANCED_RENDERER_H

#include <engine/math/Vec3.h>
#include <engine/core/models/Mesh.h>

class InstancedRenderer {
private:
    Mesh mesh;
    GLuint VAO;
    GLuint posVBO;
public:
    InstancedRenderer(Mesh mesh);
    void render(std::vector<fVec3> positions);
};

InstancedRenderer::InstancedRenderer(Mesh mesh) {
    this->mesh = std::move(mesh);
}

void InstancedRenderer::render(std::vector<fVec3> positions) {
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(fVec3)*positions.size(), &positions[0], GL_STREAM_DRAW);
//
//    program->use();
//
//    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, static_cast<GLsizei>(positions.size()));
//    glBindVertexArray(0);
}

#endif // INSTANCED_RENDERER_H