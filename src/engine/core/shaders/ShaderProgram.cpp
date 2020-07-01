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
