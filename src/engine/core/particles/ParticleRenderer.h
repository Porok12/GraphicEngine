#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include <memory>
#include <core/shaders/ShaderProgram.h>
#include "Particle.h"

class ParticleRenderer {
private:
    std::shared_ptr<ShaderProgram> program;
    static std::unique_ptr<ParticleRenderer> instance;
    Mat4 projection;
    GLuint texture;
    GLuint VAO, meshVBO, dataVBO;
    int rows, columns;
    void init();
public:

    ParticleRenderer();

    void render(const std::vector<Particle> &particles, float lifeTime);
    static ParticleRenderer* getInstance();
    ParticleRenderer* setProgram(const std::shared_ptr<ShaderProgram> &program);
    ParticleRenderer* setProjection(const Mat4 &projection);
    ParticleRenderer* setTexture(const GLuint &texture, const int &rows, const int &columns);
};

#endif // PARTICLERENDERER_H