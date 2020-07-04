#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <boost/log/trivial.hpp>

#include <math/Mat4.h>

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
    ShaderProgram& setMatrix4(std::string name, Mat4 mat4);

    GLuint getId();
};

#endif // SHADERPROGRAM_H