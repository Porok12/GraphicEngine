#include <engine/gui/UIFrame.h>
#include <engine/gui/UISelectBox.h>
#include <engine/gui/UIFrameDecorator.h>
#include <engine/core/models/Model.h>
#include <engine/core/algorithm/carpet/CreateEngine.h>
#include <engine/core/models/ModelRenderer.h>
#include "SierpinskiStage.h"

std::shared_ptr<SierpinskiStage> SierpinskiStage::instance = nullptr;

SierpinskiStage::SierpinskiStage() {
    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 300);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(300 - 50 - 10)));
        composite2->add(component);
    }

    composite2->update(800, 600);
    rootComponent = composite2;

    program = std::make_shared<ShaderProgram>("phong");

    ModelGenerator modelGenerator;
    auto vertices = modelGenerator.generateCube();
    Model cube = modelGenerator.fromVertices(vertices);
}

const std::shared_ptr<SierpinskiStage> &SierpinskiStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<SierpinskiStage>(new SierpinskiStage);
    }

    return instance;
}

void SierpinskiStage::renderUI() {
    UIStage::renderUI();
}

void SierpinskiStage::renderContent(FreeCamera &camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->setView(view);

    ModelGenerator modelGenerator;
    auto vertices = modelGenerator.generateCube();
    Model cube = modelGenerator.fromVertices(vertices);
    ModelRenderer::getInstance()->render(cube, *program);
}
