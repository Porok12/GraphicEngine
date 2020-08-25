#ifndef SHADER_LOADER
#define SHADER_LOADER

#include "../../../../src/core/shaders/Shader.h"

class ShaderLoader {
private:
    static ShaderLoader* shaderLoader;

    ShaderLoader();
public:
    static ShaderLoader get();
};

#endif // SHADER_LOADER