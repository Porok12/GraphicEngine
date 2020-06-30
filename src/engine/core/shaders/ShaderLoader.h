#ifndef SHADER_LOADER
#define SHADER_LOADER

#include "Shader.h"

class ShaderLoader {
private:
    static ShaderLoader* shaderLoader;

    ShaderLoader();
public:
    static ShaderLoader get();
    Shader loadShader(const char* name);
};

#endif // SHADER_LOADER