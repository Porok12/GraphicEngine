#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include "../utils/ResourceLoader.h"

class Shader {
private:
    GLuint shader;

    void checkForError();
    std::string loadFromFile(const char *filePath);
public:
    Shader(const char * name, GLuint shader);

    virtual ~Shader();

    GLuint getId();
};

#endif // SHADER_H