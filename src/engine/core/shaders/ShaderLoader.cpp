#include "ShaderLoader.h"

ShaderLoader* ShaderLoader::shaderLoader = nullptr;

ShaderLoader::ShaderLoader() {

}

ShaderLoader ShaderLoader::get() {
    if (shaderLoader == nullptr) {
        shaderLoader = new ShaderLoader();
    }

    return *shaderLoader;
}

Shader ShaderLoader::loadShader(const char *name) {
    return Shader();
}
