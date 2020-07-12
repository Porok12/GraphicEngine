#include <core/models/ModelRenderer.h>
#include "MeshStage.h"

std::shared_ptr<MeshStage> MeshStage::instance = nullptr;

MeshStage::MeshStage()
        : particleGenerator(2.0f) {
//    auto particleProgram = std::make_shared<ShaderProgram>("particle");
//    auto texture = ResourceLoader::loadTexture("particle.png");
//    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    auto rect2 = std::make_shared<Rectangle>(50, 50, 350, 250);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 220, 100, 100, 50);
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

    model.loadModel(ResourceLoader::getPath("cube.obj", MODEL));
}

void MeshStage::renderUI() {
    UIStage::renderUI();
}

void MeshStage::renderContent(Camera camera, double dt) {
    particleGenerator.update(dt);

    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 0, -4) * mm;

    ModelRenderer::getInstance()->setModel( Mat4::rotation(a++, fVec3(0.9, 0.6, 0.3)) * mm);
    ModelRenderer::getInstance()->setView(view);
    ModelRenderer::getInstance()->render(model);
}

const std::shared_ptr<MeshStage> &MeshStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<MeshStage>(new MeshStage);
    }

    return instance;
}