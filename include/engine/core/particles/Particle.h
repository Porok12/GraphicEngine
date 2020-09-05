#ifndef PARTICLE_H
#define PARTICLE_H

#include <GL/glew.h>
#include <algorithm>
#include <engine/math/Vec3.h>
#include <engine/math/Vec4.h>
#include <engine/math/Mat4.h>
#include <engine/core/shaders/ShaderProgram.h>
#include <engine/core/utils/ResourceLoader.h>

struct Particle {
    fVec3 Position;
    fVec3 Velocity;
    float LifeTime;
    float Transparency;
    float Size, Angle, Weight;
    int Select;

    Particle()
            : Position(0.0f), LifeTime(0.0f) { }
    Particle(const fVec3 &Position, float LifeTime)
            : Position(Position), LifeTime(LifeTime) { }
    Particle(const fVec3 &Position, float LifeTime, float Transparency)
            : Position(Position), LifeTime(LifeTime), Transparency(Transparency) { }
    Particle(const fVec3 &Position, float LifeTime, float Transparency, float Size, float Angle, int Select)
            : Position(Position), LifeTime(LifeTime), Transparency(Transparency), Size(Size), Angle(Angle), Select(Select) { }
    Particle(const fVec3 &Position, const fVec3 &Velocity, float LifeTime, float Transparency, float Size, float Angle, int Select)
            : Position(Position), Velocity(Velocity), LifeTime(LifeTime), Transparency(Transparency), Size(Size), Angle(Angle), Select(Select) { }
};

#endif // PARTICLE_H