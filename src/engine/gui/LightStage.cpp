#include "LightStage.h"

std::shared_ptr<LightStage> LightStage::instance = nullptr;

LightStage::LightStage() {
//    auto particleProgram = std::make_shared<ShaderProgram>("particle");
//    auto texture = ResourceLoader::loadTexture("particle.png");
//    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    auto rect2 = std::make_shared<Rectangle>(10, 10, 120, 320);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        composite2->add(component);

        component = std::make_shared<UIButton>("Flat", 10, 70, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){updateShading(FLAT);});
        composite2->add(component);

        component = std::make_shared<UIButton>("Gouraud", 10, 130, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){updateShading(GOURAUD);});
        composite2->add(component);

        component = std::make_shared<UIButton>("Phong", 10, 190, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){updateShading(PHONG);});
        composite2->add(component);

        component = std::make_shared<UIButton>("Blinn", 10, 250, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){updateShading(BLINN);});
        composite2->add(component);
    }

    rootComponent = composite2;

    model.enableBumpMapping(true);
    model.loadModel(ResourceLoader::getPath("sphere2.obj", MODEL));

    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    phong = std::make_shared<ShaderProgram>("light");
    gouraud = std::make_shared<ShaderProgram>("light2");
    program = phong;

}

void LightStage::renderUI() {
    UIStage::renderUI();
}

void LightStage::renderContent(Camera camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 0, -4) * mm;

    ModelRenderer::getInstance()->setModel( Mat4::rotation(a++, fVec3(0.9, 0.6, 0.3)) * mm);
    ModelRenderer::getInstance()->setView(view);


    program->use();
    program->set3f("viewPos", camera.getPos().x, camera.getPos().y, camera.getPos().z);
    program->set3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
    program->set3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    program->set3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    program->set3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
    ModelRenderer::getInstance()->render(model, *program);


    mm = Mat4::identity();
//    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, -2, -4) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<LightStage> &LightStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<LightStage>(new LightStage);
    }

    return instance;
}

void LightStage::updateShading(Shading shading) {
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
