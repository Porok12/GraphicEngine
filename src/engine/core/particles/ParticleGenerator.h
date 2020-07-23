#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include "Particle.h"
#include <boost/random.hpp>
#include <ctime>
#include <cstdint>

class ParticleGenerator {
private:
//    typedef std::vector<std::shared_ptr<Particle>> shared_vector;
//    typedef std::function<void (double, const shared_vector &)> function_update;
    using shared_vector = std::vector<std::shared_ptr<Particle>>;
    using function_update = std::function<void (double, const shared_vector &)>;
    shared_vector particles;
    shared_vector expired;

    GLuint texture;
    float lifeTime;
    float limit;
    float sizeMin, sizeMax;
    float angleMin, angleMax;
    float weightMin, weightMax;
    float transparencyMin, transparencyMax;
    float spawnRate;
    fVec3 velocityMin, velocityMax;
    fVec3 positionMin, positionMax;
    function_update updateFun;
    float size;
    int select;

    float rate, curr;
    float tmp;

    ParticleGenerator(GLuint texture,
                      float lifeTime,
                      float limit,
                      float sizeMin,
                      float sizeMax,
                      float angleMin,
                      float angleMax,
                      float weightMin,
                      float weightMax,
                      float transparencyMin,
                      float transparencyMax,
                      float spawnRate,
                      fVec3 velocityMin,
                      fVec3 velocityMax,
                      fVec3 positionMin,
                      fVec3 positionMax,
                      const function_update &updateFun,
                      int select);
    void init();
    void spawnParticle();

private:

    class GeneratorBuilder {
    private:
        GLuint texture;
        float lifeTime;
        float limit;
        float sizeMin, sizeMax;
        float angleMin, angleMax;
        float weightMin, weightMax;
        float transparencyMin, transparencyMax;
        float spawnRate;
        function_update updateFun;
        fVec3 velocityMin, velocityMax;
        fVec3 positionMin, positionMax;
        int select;

    public:
        GeneratorBuilder();

        GeneratorBuilder &setTexture(GLuint texture);
        GeneratorBuilder &setLifeTime(const float &lifeTime);
        GeneratorBuilder &setLimit(const float &limit);
        GeneratorBuilder &setSize(const float &size);
        GeneratorBuilder &setSize(const float &minSize, const float &maxSize);
        GeneratorBuilder &setAngle(const float &angle);
        GeneratorBuilder &setAngle(const float &minAngle, const float &maxAngle);
        GeneratorBuilder &setWeight(const float &weight);
        GeneratorBuilder &setWeight(const float &minWeight, const float &maxWeight);
        GeneratorBuilder &setTransparency(const float &transparency);
        GeneratorBuilder &setTransparency(const float &minTransparency, const float &maxTransparency);
        GeneratorBuilder &setSpawnRate(const float &spawnRate);
        GeneratorBuilder &setPosition(const fVec3 &position);
        GeneratorBuilder &setPosition(const fVec3 &minPosition, const fVec3 &maxPosition);
        GeneratorBuilder &setVelocity(const fVec3 &velocity);
        GeneratorBuilder &setVelocity(const fVec3 &minVelocity, const fVec3 &maxVelocity);
        GeneratorBuilder &setUpdate(const function_update &updateFun);
        GeneratorBuilder &setSelect(const int &select);

        ParticleGenerator build();
        ParticleGenerator* buildPtr();
    };
public:

    static GeneratorBuilder getBuilder();
    void update(double dt);
    const shared_vector &getParticles() const;
    float getLifeTime() const;
    GLuint getTexture() const;
};

#endif // PARTICLEGENERATOR_H