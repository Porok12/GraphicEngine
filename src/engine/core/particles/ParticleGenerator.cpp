#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(GLuint texture,
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
                                     const function_update &updateFun)
        : texture(texture), lifeTime(lifeTime), limit(limit), sizeMin(sizeMin), sizeMax(sizeMax),
          angleMin(angleMin), angleMax(angleMax), weightMin(weightMin), weightMax(weightMax),
          transparencyMin(transparencyMin), transparencyMax(transparencyMax), updateFun(updateFun) {
    init();
}

void ParticleGenerator::init() {
    particles.emplace_back(std::make_shared<Particle>(fVec3(0,2,-5), lifeTime));
    rate = 0.3f;
    curr = 0.0f;
}

void ParticleGenerator::update(double dt) {
    if (updateFun) {
        updateFun(dt, particles);
    }

    for (auto &p: particles) {
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
        spawnParticle();
    }
}

void ParticleGenerator::spawnParticle() {
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

const std::vector<std::shared_ptr<Particle>> &ParticleGenerator::getParticles() const {
    return particles;
}

float ParticleGenerator::getLifeTime() const {
    return lifeTime;
}

ParticleGenerator::GeneratorBuilder ParticleGenerator::getBuilder() {
    return ParticleGenerator::GeneratorBuilder();
}

ParticleGenerator::GeneratorBuilder::GeneratorBuilder()
        : lifeTime(1), limit(10), sizeMin(1), sizeMax(1), angleMin(0), angleMax(0), weightMin(1), weightMax(1),
          transparencyMin(1), transparencyMax(1), select(-1) {

}

ParticleGenerator ParticleGenerator::GeneratorBuilder::build() {
    return ParticleGenerator(
            this->texture,
            this->lifeTime,
            this->limit,
            this->sizeMin,
            this->sizeMax,
            this->angleMin,
            this->angleMax,
            this->weightMin,
            this->weightMax,
            this->transparencyMin,
            this->transparencyMax,
            this->updateFun
    );
}


ParticleGenerator *ParticleGenerator::GeneratorBuilder::buildPtr() {
    return new ParticleGenerator(
            this->texture,
            this->lifeTime,
            this->limit,
            this->sizeMin,
            this->sizeMax,
            this->angleMin,
            this->angleMax,
            this->weightMin,
            this->weightMax,
            this->transparencyMin,
            this->transparencyMax,
            this->updateFun
    );;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setTexture(GLuint texture)  {
    GeneratorBuilder::texture = texture;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setLifeTime(const float &lifeTime) {
    GeneratorBuilder::lifeTime = lifeTime;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setLimit(const float &limit) {
    GeneratorBuilder::limit = limit;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setSize(const float &size) {
    GeneratorBuilder::sizeMin = size;
    GeneratorBuilder::sizeMax = size;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setSize(const float &minSize, const float &maxSize) {
    GeneratorBuilder::sizeMin = minSize;
    GeneratorBuilder::sizeMax = maxSize;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setAngle(const float &angle) {
    GeneratorBuilder::angleMin = angle;
    GeneratorBuilder::angleMax = angle;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setAngle(const float &minAngle, const float &maxAngle) {
    GeneratorBuilder::angleMin = minAngle;
    GeneratorBuilder::angleMax = maxAngle;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setWeight(const float &weight) {
    GeneratorBuilder::weightMin = weight;
    GeneratorBuilder::weightMax = weight;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setWeight(const float &minWeight, const float &maxWeight) {
    GeneratorBuilder::weightMin = minWeight;
    GeneratorBuilder::weightMax = maxWeight;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setTransparency(const float &transparency) {
    GeneratorBuilder::transparencyMin = transparency;
    GeneratorBuilder::transparencyMax = transparency;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setTransparency(const float &minTransparency, const float &maxTransparency) {
    GeneratorBuilder::transparencyMin = minTransparency;
    GeneratorBuilder::transparencyMax = maxTransparency;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setUpdate(const function_update &updateFun) {
    GeneratorBuilder::updateFun = updateFun;
    return *this;
}
