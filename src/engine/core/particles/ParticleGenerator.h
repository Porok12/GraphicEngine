#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

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
    explicit ParticleGenerator(const float &lifeTime);

    void update(double dt);

    const shared_vector &getParticles() const;

    float getLifeTime() const;
};

#endif // PARTICLEGENERATOR_H