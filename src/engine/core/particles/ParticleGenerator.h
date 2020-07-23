#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include "Particle.h"

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
    function_update updateFun;

    fVec3 velocity;
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
                      const function_update &updateFun);
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
        function_update updateFun;

        int select;
        fVec3 Velocity;
        fVec3 Position;
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
        GeneratorBuilder &setUpdate(const function_update &updateFun);

        ParticleGenerator build();
        ParticleGenerator* buildPtr();
    };
public:

    static GeneratorBuilder getBuilder();

    void update(double dt);
    const shared_vector &getParticles() const;
    float getLifeTime() const;
};

#endif // PARTICLEGENERATOR_H