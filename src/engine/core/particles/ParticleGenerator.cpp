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
                                     float spawnRate,
                                     fVec3 velocityMin,
                                     fVec3 velocityMax,
                                     fVec3 positionMin,
                                     fVec3 positionMax,
                                     const function_update &updateFun,
                                     int select)
        : texture(texture), lifeTime(lifeTime), limit(limit), sizeMin(sizeMin), sizeMax(sizeMax),
          angleMin(angleMin), angleMax(angleMax), weightMin(weightMin), weightMax(weightMax),
          transparencyMin(transparencyMin), transparencyMax(transparencyMax), updateFun(updateFun),
          velocityMin(velocityMin), velocityMax(velocityMax), positionMin(positionMin), positionMax(positionMax),
          spawnRate(spawnRate), select(select) {
    init();
}

void ParticleGenerator::init() {
//    particles.emplace_back(std::make_shared<Particle>(fVec3(0,2,-5), lifeTime));
    rate = 0.3f;
    curr = 0.0f;
}

void ParticleGenerator::update(double dt) {
    if (updateFun) {
        updateFun(dt, particles);
    }

    for (auto &p: particles) {
//        std::cout << p->Transparency << std::endl;
        if (p->LifeTime < 0.02) {
            if (std::find(expired.begin(), expired.end(), p) == expired.end()) {
                expired.push_back(p);
            }
            continue;
        }
    }

    curr += dt;
    if (curr > spawnRate) {
        curr = 0.0f;
        spawnParticle();
    }
}

void ParticleGenerator::spawnParticle() {
    static std::time_t now = std::time(0);
    static boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};
    
    auto it = expired.begin();
    if (it != expired.end()) {

        (*it)->LifeTime = lifeTime;

        if (velocityMin.x == velocityMax.x && velocityMin.y == velocityMax.y && velocityMin.z == velocityMax.z) {
            (*it)->Velocity = velocityMin;
        } else {
            boost::random::uniform_real_distribution<> x_dist{velocityMin.x, velocityMax.x+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> y_dist{velocityMin.y, velocityMax.y+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> z_dist{velocityMin.z, velocityMax.z+std::numeric_limits<float>::min()};
            (*it)->Velocity = fVec3(x_dist(gen), y_dist(gen), z_dist(gen));
        }
        
        if (positionMin.x == positionMax.x && positionMin.y == positionMax.y && positionMin.z == positionMax.z) {
            (*it)->Position = positionMin;
        } else {
            boost::random::uniform_real_distribution<> x_dist{positionMin.x, positionMax.x+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> y_dist{positionMin.y, positionMax.y+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> z_dist{positionMin.z, positionMax.z+std::numeric_limits<float>::min()};
            (*it)->Position = fVec3(x_dist(gen), y_dist(gen), z_dist(gen));
        }

        if (transparencyMin == transparencyMax) {
            (*it)->Transparency = transparencyMin;
        } else {
            boost::random::uniform_real_distribution<> dist{transparencyMin, transparencyMax+std::numeric_limits<float>::min()};
            (*it)->Transparency = dist(gen);
        }

        int select = this->select;
        if (select != -1) {
            boost::random::uniform_int_distribution<> dist{0, select-1};
            (*it)->Select = dist(gen);
        }
        
        if (sizeMin == sizeMax) {
            (*it)->Size = sizeMin;
        } else {
            boost::random::uniform_real_distribution<> dist{sizeMin, sizeMax+std::numeric_limits<float>::min()};
            (*it)->Size = dist(gen);
        }
        

        tmp += 0.1f;
        expired.erase(it);
    } else if (particles.size() < limit) {
        float x;
        float y;
        float z;
        float t;
        int select = this->select;
        float s;
        fVec3 velocity;

        if (select != -1) {
            boost::random::uniform_int_distribution<> dist{0, select-1};
            select = dist(gen);
        }

        if (positionMin.x == positionMax.x && positionMin.y == positionMax.y && positionMin.z == positionMax.z) {
            x = positionMin.x;
            y = positionMin.y;
            z = positionMin.z;
        } else {
            boost::random::uniform_real_distribution<> x_dist{positionMin.x, positionMax.x+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> y_dist{positionMin.y, positionMax.y+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> z_dist{positionMin.z, positionMax.z+std::numeric_limits<float>::min()};
            x = x_dist(gen);
            y = y_dist(gen);
            z = z_dist(gen);
        }

        if (velocityMin.x == velocityMax.x && velocityMin.y == velocityMax.y && velocityMin.z == velocityMax.z) {
            velocity = velocityMin;
        } else {
            boost::random::uniform_real_distribution<> x_dist{velocityMin.x, velocityMax.x+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> y_dist{velocityMin.y, velocityMax.y+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> z_dist{velocityMin.z, velocityMax.z+std::numeric_limits<float>::min()};
            velocity = fVec3(x_dist(gen), y_dist(gen), z_dist(gen));
        }

        if (transparencyMin == transparencyMax) {
            t = transparencyMin;
        } else {
//            boost::random::uniform_real_distribution<> t_dist{transparencyMin, transparencyMax+std::numeric_limits<float>::min()};
            boost::random::uniform_real_distribution<> dist{transparencyMin, transparencyMax+std::numeric_limits<float>::min()};
            t = dist(gen);
        }

        if (sizeMin == sizeMax) {
            s = sizeMin;
        } else {
            boost::random::uniform_real_distribution<> dist{sizeMin, sizeMax+std::numeric_limits<float>::min()};
            s = dist(gen);
        }

        particles.emplace_back(std::make_shared<Particle>(fVec3(x, y, z), velocity, lifeTime, t, s, 0, select));
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

GLuint ParticleGenerator::getTexture() const {
    return texture;
}

ParticleGenerator::GeneratorBuilder::GeneratorBuilder()
        : lifeTime(1), limit(10), sizeMin(1), sizeMax(1), angleMin(0), angleMax(0), weightMin(1), weightMax(1),
          transparencyMin(1), transparencyMax(1), positionMin(0), positionMax(0), velocityMin(0), velocityMax(0),
          spawnRate(1), select(-1) {

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
            this->spawnRate,
            this->velocityMin,
            this->velocityMax,
            this->positionMin,
            this->positionMax,
            this->updateFun,
            this->select
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
            this->spawnRate,
            this->velocityMin,
            this->velocityMax,
            this->positionMin,
            this->positionMax,
            this->updateFun,
            this->select
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

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setSpawnRate(const float &spawnRate) {
    GeneratorBuilder::spawnRate = spawnRate;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setVelocity(const fVec3 &velocity) {
    GeneratorBuilder::velocityMin = velocity;
    GeneratorBuilder::velocityMax = velocity;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setVelocity(const fVec3 &minVelocity, const fVec3 &maxVelocity) {
    GeneratorBuilder::velocityMin = minVelocity;
    GeneratorBuilder::velocityMax = maxVelocity;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setPosition(const fVec3 &position) {
    GeneratorBuilder::positionMin = position;
    GeneratorBuilder::positionMax = position;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setPosition(const fVec3 &minPosition, const fVec3 &maxPosition) {
    GeneratorBuilder::positionMin = minPosition;
    GeneratorBuilder::positionMax = maxPosition;
    return *this;
}

ParticleGenerator::GeneratorBuilder &
ParticleGenerator::GeneratorBuilder::setUpdate(const function_update &updateFun) {
    GeneratorBuilder::updateFun = updateFun;
    return *this;
}

ParticleGenerator::GeneratorBuilder &ParticleGenerator::GeneratorBuilder::setSelect(const int &select) {
    GeneratorBuilder::select = select;
    return *this;
}
