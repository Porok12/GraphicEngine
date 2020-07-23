#include <core/models/ModelRenderer.h>
#include <gui/UISlider.h>
#include "MeshStage.h"

std::shared_ptr<MeshStage> MeshStage::instance = nullptr;

MeshStage::MeshStage()
        : particleGenerator(2.0f) {
//    auto particleProgram = std::make_shared<ShaderProgram>("particle");
//    auto texture = ResourceLoader::loadTexture("particle.png");
//    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 500);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(500 - 50 - 10)));
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 30, 0.01, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            rotationSpeed = f;
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(10)));
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 30, 0.01, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            rotationX = f;
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(50)));
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 30, 0.01, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            rotationY = f;
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(100)));
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 30, 0, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            rotationZ = f;
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(150)));
        composite2->add(component);
    }

//    composite2->setConstraints((new RectangleConstraints())->setX(new FixedConstraint(10))->setY(new FixedConstraint(10)));
    composite2->update(800, 600);
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

    tmp += rotationSpeed;

    ModelRenderer::getInstance()->setModel( Mat4::rotation(tmp, fVec3(rotationX, rotationY, rotationZ)) * mm);
    ModelRenderer::getInstance()->setView(view);
    ModelRenderer::getInstance()->render(model);
}

const std::shared_ptr<MeshStage> &MeshStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<MeshStage>(new MeshStage);
    }

    return instance;
}