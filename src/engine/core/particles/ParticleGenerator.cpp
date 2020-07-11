#include "ParticleGenerator.h"

void ParticleGenerator::init() {
    particles.emplace_back(fVec3(0,2,-5), lifeTime);
    rate = 0.5f;
    curr = 0.0f;
}

ParticleGenerator::ParticleGenerator(float lifeTime)
        : lifeTime(lifeTime), velocity(0.0f) {
    init();
}

void ParticleGenerator::update(double dt) {
//    velocity += fVec3(0.0f, -9.81f, 0.0f) * dt * 0.5f;


    for (auto &p: particles) {
        if (p.LifeTime < 0) continue;
        p.LifeTime -= dt;
        p.Velocity += fVec3(0.0f, -9.81f, 0.0f) * dt * 0.5f;
        p.Position += p.Velocity * dt * 0.2;
    }

    curr += dt;
    if (curr > rate) {
        curr = 0.0f;
        particles.emplace_back(fVec3(0,2,-5), lifeTime);
    }
}

const std::vector<Particle> &ParticleGenerator::getParticles() const {
    return particles;
}

float ParticleGenerator::getLifeTime() const {
    return lifeTime;
}
