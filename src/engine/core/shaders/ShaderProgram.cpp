#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char *name) {
    program = glCreateProgram();
    Shader vertex(name, GL_VERTEX_SHADER);
    Shader fragment(name, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertex.getId());
    glAttachShader(program, fragment.getId());

    glLinkProgram(program);
    BOOST_LOG_TRIVIAL(debug) << "Shader program has been linked: " << name;

    checkForErrors(name);
}

void ShaderProgram::checkForErrors(const char* name) {
    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        BOOST_LOG_TRIVIAL(error) << "Program linking error: " << infoLog;
    } else {
        BOOST_LOG_TRIVIAL(debug) << "Program " << name << " linked successfully";
    }
}

ShaderProgram::~ShaderProgram() {
    BOOST_LOG_TRIVIAL(debug) << "Program destructor";
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