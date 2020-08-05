#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <math/Mat4.h>
#include "Shader.h"

class ShaderProgram {
private:
    GLuint program;

    void checkForErrors(const char* name);
public:
    ShaderProgram(const char * name);
    ~ShaderProgram();

    ShaderProgram& use();
    ShaderProgram& setMatrix4(std::string name, Mat4 mat4);
    ShaderProgram& set3f(std::string name, float x, float y, float z);
    ShaderProgram& set3f(std::string name, fVec3 v);
    ShaderProgram& set4f(std::string name, float x, float y, float z, float w);
    ShaderProgram& set1i(std::string name, int i);
    ShaderProgram& set1f(std::string name, float f);
    ShaderProgram& set1b(std::string name, bool val);

    GLuint getId() const;
};

#endif // SHADERPROGRAM_H