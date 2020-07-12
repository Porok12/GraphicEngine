#include "ParticleGenerator.h"

void ParticleGenerator::init() {
    particles.emplace_back(std::make_shared<Particle>(fVec3(0,2,-5), lifeTime));
    rate = 0.3f;
    curr = 0.0f;
}

ParticleGenerator::ParticleGenerator(const float &lifeTime)
        : lifeTime(lifeTime), velocity(0.0f) {
    init();
}

void ParticleGenerator::update(double dt) {
    for (auto &p: particles) {
        p->LifeTime -= dt;
        p->Velocity += fVec3(0.0f, -9.81f, 0.0f) * dt * 0.5f;
        p->Position += p->Velocity * dt * 0.4;

        if (p->LifeTime < 0) {
            if (std::find(expired.begin(), expired.end(), p) == expired.end()) {
                expired.push_back(p);
            }
            continue;
        }
    }

    curr += dt;
    if (curr > rate) {
        curr = 0.0f;
        auto it = expired.begin();
        if (it != expired.end()) {
            (*it)->LifeTime = lifeTime;
            (*it)->Velocity = fVec3(5*std::sin(tmp), 2, std::cos(tmp));
            (*it)->Position = fVec3(0, 2, -5);
            tmp += 0.1f;
            expired.erase(it);
        } else {
            particles.emplace_back(std::make_shared<Particle>(fVec3(0, 2, -5), lifeTime));
        }
    }
}

const std::vector<std::shared_ptr<Particle>> &ParticleGenerator::getParticles() const {
    return particles;
}

float ParticleGenerator::getLifeTime() const {
    return lifeTime;
}
