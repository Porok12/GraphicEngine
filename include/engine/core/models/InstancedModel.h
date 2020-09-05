#ifndef INSTANCED_MODEL
#define INSTANCED_MODEL

#include "InstancedMesh.h"

class InstancedModel {
private:
    InstancedMesh mesh;

public:
    explicit InstancedModel() = default;
    void loadMesh(InstancedMesh mesh);
    void draw(const ShaderProgram &shaderProgram) const;
};

#endif // INSTANCED_MODEL