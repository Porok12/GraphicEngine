#ifndef PARTICLE_H
#define PARTICLE_H

#include <GL/glew.h>
#include <algorithm>
#include <math/Vec3.h>
#include <math/Vec4.h>
#include <math/Mat4.h>
#include <core/shaders/ShaderProgram.h>
#include <core/utils/ResourceLoader.h>

struct Particle {
    fVec3 Position;
    fVec3 Velocity;
    float LifeTime;

    Particle() : Position(0.0f), LifeTime(0.0f) { }
    Particle(const fVec3 &Position, float LifeTime) : Position(Position), LifeTime(LifeTime) { }
};

#endif // PARTICLE_H