#include "ParticlesStage.h"

std::shared_ptr<ParticleStage> ParticleStage::instance = nullptr;

ParticleStage::ParticleStage() {
//    auto particleProgram = std::make_shared<ShaderProgram>("particle");
//    auto texture = ResourceLoader::loadTexture("particle.png");
//    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

//    auto texture = ResourceLoader::loadTexture("Cloud.tga");
//    ParticleRenderer::getInstance()->setTexture(texture, 8, 8);
//
//    texture = ResourceLoader::loadTexture("Explosion.tga");
//    ParticleRenderer::getInstance()->setTexture(texture, 5, 5);
//
//    texture = ResourceLoader::loadTexture("CandleSmoke.tga");
//    ParticleRenderer::getInstance()->setTexture(texture, 20, 4);
//
//    texture = ResourceLoader::loadTexture("SnowFlakes.png");
//    ParticleRenderer::getInstance()->setTexture(texture, 2, 2);


    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 200);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(200 - 50 - 10)));
        composite2->add(component);

        component.reset(new UISelectBox(50, 300, 150, 50));
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"Flame", "Snow"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([](int i){std::cout << i << std::endl;});
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(10)));
        composite2->add(component);
    }

    composite2->update(800, 600);
    rootComponent = composite2;



    auto p1 = ParticleGenerator::getBuilder()
            .setTexture(0)
            .setLifeTime(2)
            .setUpdate([](double dt, const std::vector<std::shared_ptr<Particle>> &particles){
                for (auto &p: particles) {
                    p->LifeTime -= dt;
                    p->Velocity += fVec3(0.0f, -9.81f, 0.0f) * dt * 0.5f;
                    p->Position += p->Velocity * dt * 0.4;
                }
            })
            .buildPtr();
    particleGenerator = std::unique_ptr<ParticleGenerator>(p1);
}

void ParticleStage::renderUI() {
    UIStage::renderUI();
}

void ParticleStage::renderContent(Camera camera, double dt) {
    particleGenerator->update(dt);

    glDisable(GL_DEPTH_TEST);
    Mat4 view = camera.getViewMatrix();
    ParticleRenderer::getInstance()
            ->setRight(camera.getRight())
            ->setUp(camera.getUp())
            ->setCamera(camera.getPos())
            ->setView(view)
            ->render(particleGenerator->getParticles(), particleGenerator->getLifeTime());
}

const std::shared_ptr<ParticleStage> &ParticleStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<ParticleStage>(new ParticleStage);
    }

    return instance;
}
