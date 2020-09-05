#include <engine/core/models/InstancedModel.h>

void InstancedModel::loadMesh(InstancedMesh mesh) {
    this->mesh = std::move(mesh);
}

void InstancedModel::draw(const ShaderProgram &shaderProgram) const {
    mesh.draw(); // shaderProgram
}
