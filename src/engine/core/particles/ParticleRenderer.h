#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include <memory>
#include <core/shaders/ShaderProgram.h>
#include "Particle.h"

class ParticleRenderer {
    struct ParticleData {
        float x, y, z, lifeTime;

        ParticleData(float x, float y, float z, float lifeTime);
    };
private:
    std::shared_ptr<ShaderProgram> program;
    static std::unique_ptr<ParticleRenderer> instance;
    Mat4 projection, view;
    fVec3 cameraPos, right, up;
    GLuint texture;
    GLuint VAO, meshVBO, dataVBO;
    int rows, columns;
    void init();

public:

    ParticleRenderer();

    void render(const std::vector<std::shared_ptr<Particle>> &particles, float lifeTime);
    static ParticleRenderer* getInstance();
    ParticleRenderer* setProgram(const std::shared_ptr<ShaderProgram> &program);
    ParticleRenderer* setProjection(const Mat4 &projection);
    ParticleRenderer* setTexture(const GLuint &texture, const int &rows, const int &columns);
    ParticleRenderer* setView(const Mat4 &view);
    ParticleRenderer* setCamera(fVec3 cameraPos);
    ParticleRenderer *setRight(const fVec3 &right);
    ParticleRenderer *setUp(const fVec3 &up);
};

#endif // PARTICLERENDERER_H