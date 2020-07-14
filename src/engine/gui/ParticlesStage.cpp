#include "ParticlesStage.h"

std::shared_ptr<ParticleStage> ParticleStage::instance = nullptr;

ParticleStage::ParticleStage()
        : particleGenerator(2.0f) {
//    auto particleProgram = std::make_shared<ShaderProgram>("particle");
//    auto texture = ResourceLoader::loadTexture("particle.png");
//    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    auto rect2 = std::make_shared<Rectangle>(10, 10, 120, 70);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
//        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback(fun);
//        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([&stageManager]() {
//            if (auto manager = stageManager.lock()) {
//                manager->setStage(Stages::PARTICLES);
//            }
//        });
        composite2->add(component);
    }

    rootComponent = composite2;
}

void ParticleStage::renderUI() {
    UIStage::renderUI();
}

void ParticleStage::renderContent(Camera camera, double dt) {
    particleGenerator.update(dt);

    glDisable(GL_DEPTH_TEST);
    Mat4 view = camera.getViewMatrix();
    ParticleRenderer::getInstance()
            ->setRight(camera.getRight())
            ->setUp(camera.getUp())
            ->setCamera(camera.getPos())
            ->setView(view)
            ->render(particleGenerator.getParticles(), particleGenerator.getLifeTime());
}

const std::shared_ptr<ParticleStage> &ParticleStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<ParticleStage>(new ParticleStage);
    }

    return instance;
}
