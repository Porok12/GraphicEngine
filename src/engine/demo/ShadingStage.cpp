#include <core/light/Materials.h>
#include <gui/UISelectBox.h>
#include "ShadingStage.h"

std::shared_ptr<ShadingStage> ShadingStage::instance = nullptr;

ShadingStage::ShadingStage() {
    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 300);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(300 - 50 - 10)));
        composite2->add(component);

        component = std::make_shared<UISelectBox>(10, 10, 150, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"Flat", "Gourand", "Phong", "Blinn"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int option){
            updateShading(static_cast<Shading>(option));
        });
        std::dynamic_pointer_cast<UISelectBox>(component)->setConstraints(
                (new RectangleConstraints())->setX(new CenterConstraint())->setY(new FixedConstraint(10)));
        composite2->add(component);
    }

    composite2->update(800, 600);
    rootComponent = composite2;

    model.enableBumpMapping(true);
    model.loadModel(ResourceLoader::getPath("sphere2.obj", MODEL));

    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    phong = std::make_shared<ShaderProgram>("phong");
    gouraud = std::make_shared<ShaderProgram>("gouraud");
//    program = phong;
    updateShading(FLAT);
}

void ShadingStage::renderUI() {
    UIStage::renderUI();
}

void ShadingStage::renderContent(Camera camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 0, -4) * mm;
    ModelRenderer::getInstance()->setModel( Mat4::rotation(a++, fVec3(0.9, 0.6, 0.3)) * mm);
    ModelRenderer::getInstance()->setView(view);


    program->use();
    program->set3f("material.ambient", GOLD.ambient);
    program->set3f("material.diffuse", GOLD.diffuse);
    program->set3f("material.specular", GOLD.specular);
    program->set1f("material.shininess", GOLD.shininess);
    program->set3f("viewPos", camera.getPos());
    program->set3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
    program->set3f("dirLight.ambient", 1.0f, 1.0f, 1.0f);
    program->set3f("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
    program->set3f("dirLight.specular", 1.0f, 1.0f, 1.0f);
    ModelRenderer::getInstance()->render(model, *program);


    mm = Mat4::identity();
    mm = Mat4::translate(0, -2, -4) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    program->set3f("material.ambient", EMERALD.ambient);
    program->set3f("material.diffuse", EMERALD.diffuse);
    program->set3f("material.specular", EMERALD.specular);
    program->set1f("material.shininess", EMERALD.shininess);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<ShadingStage> &ShadingStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<ShadingStage>(new ShadingStage);
    }

    return instance;
}

void ShadingStage::updateShading(Shading shading) {
    switch (shading) {
        case FLAT:
            program = phong;
            model.useFlatNormals(true);
            plane.useFlatNormals(true);
            break;
        case GOURAUD:
            program = gouraud;
            model.useFlatNormals(false);
            plane.useFlatNormals(false);
            break;
        case PHONG:
            program = phong;
            program->use();
            program->set1b("blinn", false);
            model.useFlatNormals(false);
            plane.useFlatNormals(false);
            break;
        case BLINN:
            program = phong;
            program->use();
            program->set1b("blinn", true);
            model.useFlatNormals(false);
            plane.useFlatNormals(false);
            break;
    }
}
