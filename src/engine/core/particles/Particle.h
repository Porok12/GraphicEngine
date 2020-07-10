#ifndef PARTICLE_H
#define PARTICLE_H

#include <core/utils/ResourceLoader.h>
#include <math/Vec3.h>
#include <math/Vec4.h>
#include <math/Mat4.h>
#include <GL/glew.h>
#include <algorithm>
#include <core/shaders/ShaderProgram.h>

struct Particle {
    fVec3 Position, Velocity;
    fVec4 Color;
    float LifeTime;

    Particle()
            : Position(0.0f), Velocity(0.0f), Color(1.0f), LifeTime(0.0f) { }

    void update(float dt) {
        LifeTime -= dt;
        Velocity += fVec3(0.0f, -9.81f, 0.0f) * dt * 0.5f;
        Position += Velocity * dt;
    }
};

class particlesTest {
private:
    std::shared_ptr<ShaderProgram> particleProgram;
    GLuint texture;
    GLuint VAO, VBO;
    unsigned int quadVAO;
    unsigned int billboardVAO;
    GLuint instanceVAO;
    GLuint instanceVBO;
    std::vector<Particle> particles;
    float time;
    float tempTime;
    int iter = 0;
public:
//    ~particlesTest();


    void init();
    void update(float dt, fVec3 camera);
    void draw(Mat4 projection, Mat4 view, fVec3 camera);
//    void draw2(Mat4 projection, Mat4 view, fVec3 camera);


};

#endif // PARTICLE_H