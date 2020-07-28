#include "ParticlesStage.h"

std::shared_ptr<ParticleStage> ParticleStage::instance = nullptr;

ParticleStage::ParticleStage() {
    texFire = ResourceLoader::loadTexture("particle.png");
    texCloud = ResourceLoader::loadTexture("Cloud.tga");
    texExplosion = ResourceLoader::loadTexture("Explosion.tga");
    texCandleSmoke = ResourceLoader::loadTexture("CandleSmoke.tga");
    texSnowFlakes = ResourceLoader::loadTexture("SnowFlakes.png");

    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 500);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(500 - 50 - 10)));
        composite2->add(component);

        component.reset(new UISelectBox(50, 300, 150, 50));
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"Flame", "Cloud", "Explosion", /*"Smoke",*/ "Flakes"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int i){changeGenerator(i);});
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(10)));
        composite2->add(component);
    }


    composite2->update(800, 600);
    rootComponent = composite2;
    changeGenerator(0);
}

void ParticleStage::renderUI() {
    UIStage::renderUI();
}

void ParticleStage::renderContent(FreeCamera camera, double dt) {
    particleGenerator->update(dt);

    glDisable(GL_DEPTH_TEST);
    Mat4 view = camera.getViewMatrix();
    ParticleRenderer::getInstance()
            ->setRight(camera.getRight())
            ->setUp(camera.getUp())
            ->setCamera(camera.getPos())
            ->setView(view)
            ->render(particleGenerator.get());
}

const std::shared_ptr<ParticleStage> &ParticleStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<ParticleStage>(new ParticleStage);
    }

    return instance;
}

void ParticleStage::changeGenerator(int i) {
    switch (i) {
        case 0:
            ParticleRenderer::getInstance()->setTexture(texFire, 8, 8);
            particleGenerator = std::unique_ptr<ParticleGenerator>(
                    ParticleGenerator::getBuilder()
                            .setTexture(texFire)
                            .setLifeTime(1.5)
                            .setSpawnRate(0.3)
                            .setPosition(fVec3(0.2, -1.0, -4))
                            .setVelocity(fVec3(-0.2, 0.0, -0.2), fVec3(0.2, 0.1, 0.2))
                            .setTransparency(0.0)
                            .setUpdate([](double dt, const std::vector<std::shared_ptr<Particle>> &particles){
                                for (auto &p: particles) {
                                    p->LifeTime -= dt;
                                    p->Velocity += fVec3(1.0f, 10.0f, 1.0f) * dt * 0.5f;
                                    p->Position += p->Velocity * dt * 0.4;
                                    p->Transparency = std::sin(2*0.66*(1.5 - p->LifeTime)*M_PI/2);
                                }
                            }).buildPtr());
            break;
        case 1:
            ParticleRenderer::getInstance()->setTexture(texCloud, 8, 8);
            particleGenerator = std::unique_ptr<ParticleGenerator>(
                    ParticleGenerator::getBuilder()
                            .setTexture(texCloud)
                            .setLifeTime(10)
                            .setPosition(fVec3(-1.2, -0.4, -1.2-4), fVec3(1.2, 0.4, 1.2-4))
                            .setVelocity(fVec3(0))
                            .setLimit(6)
                            .setSpawnRate(1)
                            .setTransparency(0)
                            .setUpdate([](double dt, const std::vector<std::shared_ptr<Particle>> &particles){
                                for (auto &p: particles) {
                                    p->LifeTime -= dt;
                                    if (p->LifeTime >= 8) {
                                        p->Transparency = std::sin((10.0 - p->LifeTime)*M_PI/4);
                                    }
                                    if (p->LifeTime <= 2) {
                                        p->Transparency = std::cos((2.0 - p->LifeTime)*M_PI/4);
                                    }

                                    p->Position.y = std::sin(p->LifeTime) * 0.2;
                                }
                            }).buildPtr());
            break;
        case 2:
            ParticleRenderer::getInstance()->setTexture(texExplosion, 5, 5);
            particleGenerator = std::unique_ptr<ParticleGenerator>(
                    ParticleGenerator::getBuilder()
                            .setTexture(texExplosion)
                            .setLifeTime(1.2)
                            .setSpawnRate(0.15)
                            .setLimit(16)
                            .setPosition(fVec3(-0.5, -0.2, -0.5-4), fVec3(0.5, 0.2, 0.5-4))
                            .setVelocity(fVec3(-1.8, 0.2, -1.2), fVec3(1.8, 1.4, 1.2))
                            .setUpdate([](double dt, const std::vector<std::shared_ptr<Particle>> &particles){
                                for (auto &p: particles) {
                                    p->LifeTime -= dt;
                                    p->Velocity += fVec3(0.0f, -9.81f, 0.0f) * dt * -0.5f;
                                    p->Position += p->Velocity * dt * 0.4;
                                    if (p->LifeTime < 0.2) {
                                        p->Transparency = std::cos(5*(0.2 - p->LifeTime)*M_PI/2);
                                    }
                                }
                            }).buildPtr());
            break;
        case 3:
            ParticleRenderer::getInstance()->setTexture(texSnowFlakes, 2, 2);
            particleGenerator = std::unique_ptr<ParticleGenerator>(
                    ParticleGenerator::getBuilder()
                            .setTexture(texSnowFlakes)
                            .setLifeTime(3.5)
                            .setPosition(fVec3(-2.5, 2.9, -3.0-4), fVec3(2.5, 3.5, 1.0-4))
                            .setVelocity(fVec3(-1.0, -8.0, -1.0), fVec3(1.0, -3.0, 1.0))
                            .setSelect(4)
                            .setSize(0.1, 0.4)
                            .setSpawnRate(0.1)
                            .setLimit(30)
                            .setUpdate([](double dt, const std::vector<std::shared_ptr<Particle>> &particles){
                                static std::time_t now = std::time(0);
                                static boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};

                                boost::random::uniform_real_distribution<> dist{-1, 1};
                                fVec3 wind = fVec3(0);
                                if (dist(gen) < -0.8) {
                                    wind.y = dist(gen) * 20;
                                    wind.x = dist(gen) * 80;
                                    wind.z = dist(gen) * 80;
                                }

                                for (auto &p: particles) {
                                    p->LifeTime -= dt;
                                    p->Velocity += fVec3(dist(gen), -9.81f, dist(gen)) * dt * 0.02f + wind * dt;
                                    p->Position += p->Velocity * dt * 0.4;
                                }
                            }).buildPtr());
            break;
    }

}
