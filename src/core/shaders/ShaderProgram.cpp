#include <engine/core/shaders/ShaderProgram.h>
#include <GL/glew.h>
#include "Shader.h"

ShaderProgram::ShaderProgram(const char *name) {
    program = glCreateProgram();
    Shader vertex(name, GL_VERTEX_SHADER);
    Shader fragment(name, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertex.getId());
    glAttachShader(program, fragment.getId());

    glLinkProgram(program);
    std::cout << "Shader program has been linked: " << name << std::endl;

    checkForErrors(name);
}

void ShaderProgram::checkForErrors(const char* name) {
    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Program linking error: " << infoLog << std::endl;
    } else {
        std::cout << "Program " << name << " linked successfully" << std::endl;
    }
}

ShaderProgram::~ShaderProgram() {
    std::cout << "Program destructor" << std::endl;
    glDeleteProgram(program);
}

ShaderProgram &ShaderProgram::use() {
    glUseProgram(program);
    return *this;
}

GLuint ShaderProgram::getId() const {
    return program;
}

ShaderProgram &ShaderProgram::setMatrix4(std::string name, Mat4 mat4) {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, mat4.ptr());
    return *this;
}

ShaderProgram &ShaderProgram::set3f(std::string name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
    return *this;
}

ShaderProgram &ShaderProgram::set3f(std::string name, fVec3 v) {
    glUniform3f(glGetUniformLocation(program, name.c_str()), v.x, v.y, v.z);
    return *this;
}

ShaderProgram &ShaderProgram::set4f(std::string name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
    return *this;
}

ShaderProgram &ShaderProgram::set1i(std::string name, int i) {
    glUniform1i(glGetUniformLocation(program, name.c_str()), i);
    return *this;
}

ShaderProgram &ShaderProgram::set1f(std::string name, float f) {
    glUniform1f(glGetUniformLocation(program, name.c_str()), f);
    return *this;
}

ShaderProgram &ShaderProgram::set1b(std::string name, bool val) {
    glUniform1i(glGetUniformLocation(program, name.c_str()), val);
    return *this;
}
