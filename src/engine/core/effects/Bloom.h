#ifndef BLOOM_H
#define BLOOM_H

#include <GL/glew.h>
#include <boost/log/trivial.hpp>
#include <core/shaders/ShaderProgram.h>

class Bloom {
private:
    GLuint quadVAO = 0;
    GLuint quadVBO;
    GLuint FBOs[2];
    GLuint textures[2];
    std::shared_ptr<ShaderProgram> program;
    std::array<double, 32> kernel;
    unsigned int kernelSize = 6;
    double sigma = 1.75;

    void updateKernel();
    void calculateKernel();
    void drawQuad();
public:
    Bloom();
    ~Bloom();

    const GLuint & apply(const GLuint &textureID);
};

#endif // BLOOM_H