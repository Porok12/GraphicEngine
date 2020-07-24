#ifndef BLOOM_H
#define BLOOM_H

#include <GL/glew.h>
#include <boost/log/trivial.hpp>
#include <core/shaders/ShaderProgram.h>
#include <boost/math/distributions/normal.hpp>

#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 1024

class Bloom {
private:
    GLuint quadVAO = 0;
    GLuint quadVBO;
    GLuint FBOs[2];
    GLuint textures[2];
    std::shared_ptr<ShaderProgram> program;
    std::array<double, 32> kernel;
    unsigned int kernelSize = 1;
    unsigned int iterations = 0;
    double sigma = 0.1;

    void calculateKernel();
    void drawQuad();
    void updateKernel();
public:
    Bloom();
    ~Bloom();

    const GLuint & apply(const GLuint &textureID);

    void setKernelSize(unsigned int kernelSize);
    void setSigma(double sigma);

    void setIterations(unsigned int iterations);
};

#endif // BLOOM_H