#ifndef PARTICLEGNERATOR_H
#define PARTICLEGNERATOR_H

#include "Particle.h"

class ParticleGenerator {
private:
    typedef std::vector<std::shared_ptr<Particle>> shared_vector;
    shared_vector particles;
    shared_vector expired;
    float lifeTime;
    fVec3 velocity;
    float rate, curr;
    float tmp;

    void init();
public:
    ParticleGenerator(float lifeTime);

    void update(double dt);

    const shared_vector &getParticles() const;

    float getLifeTime() const;
};

#endif // PARTICLEGNERATOR_H