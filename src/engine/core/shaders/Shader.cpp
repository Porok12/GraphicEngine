#include "Shader.h"

Shader::Shader(const char *name, GLuint shader) {
    std::string root_path = ResourceLoader::getPath(name, SHADER);
    switch (shader) {
        case GL_VERTEX_SHADER:
            root_path.append(".vert");
            break;
        case GL_FRAGMENT_SHADER:
            root_path.append(".frag");
            break;
    }

    this->shader = glCreateShader(shader);

    std::string source = loadFromFile(root_path.c_str());
    const GLchar *data = source.c_str();

    glShaderSource(this->shader, 1, &data, NULL);
    glCompileShader(this->shader);

    BOOST_LOG_TRIVIAL(debug)
        << (root_path.find("vert") != std::string::npos ? "Vertex" : "Fragment")
        << " shader has been compiled: " << name;

    checkForError();
}

void Shader::checkForError() {
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        BOOST_LOG_TRIVIAL(error) << "Shader compilation failed: " << infoLog;
    }
}

std::string Shader::loadFromFile(const char *filePath) {
    std::ifstream file(filePath);

    if (file.good()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        const std::string tmp = buffer.str();
        return tmp;
    } else {
        BOOST_LOG_TRIVIAL(error) << "There is not such file: " << filePath;
        return "";
    }
}

GLuint Shader::getId() {
    return this->shader;
}

Shader::~Shader() {
    glDeleteShader(this->shader);
}
