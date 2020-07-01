#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <boost/log/trivial.hpp>

#include "Shader.h"

class ShaderProgram {
private:
    GLuint program;

    void checkForErrors();
    void compile();
public:
    ShaderProgram(const char * name);
    ~ShaderProgram();

    ShaderProgram& use();
};

#endif // SHADERPROGRAM_H