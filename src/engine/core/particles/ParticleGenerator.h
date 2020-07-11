#ifndef PARTICLEGNERATOR_H
#define PARTICLEGNERATOR_H

#include "Particle.h"

class ParticleGenerator {
private:
    std::vector<Particle> particles;
    float lifeTime;
    fVec3 velocity;
    float rate, curr;


    void init();
public:
    ParticleGenerator(float lifeTime);

    void update(double dt);

    const std::vector<Particle> &getParticles() const;

    float getLifeTime() const;
};

#endif // PARTICLEGNERATOR_H