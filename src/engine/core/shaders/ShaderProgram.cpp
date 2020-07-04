#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char *name) {
    program = glCreateProgram();
    Shader vertex(name, GL_VERTEX_SHADER);
    Shader fragment(name, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertex.getId());
    glAttachShader(program, fragment.getId());

    glLinkProgram(program);
    BOOST_LOG_TRIVIAL(debug) << "Shader program has been linked: " << name;

    checkForErrors();
}

void ShaderProgram::checkForErrors() {
    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        BOOST_LOG_TRIVIAL(error) << "Program linking error: " << infoLog;
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program);
}

ShaderProgram &ShaderProgram::use() {
    glUseProgram(program);
    return *this;
}

GLuint ShaderProgram::getId() {
    return program;
}

ShaderProgram &ShaderProgram::setMatrix4(std::string name, Mat4 mat4) {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, mat4.ptr());
    return *this;
}
