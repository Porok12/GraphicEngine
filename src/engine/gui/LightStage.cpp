#include <core/light/Materials.h>
#include "LightStage.h"

std::shared_ptr<LightStage> LightStage::instance = nullptr;

LightStage::LightStage()
        : dirLight(fVec3(1.0), fVec3(1.0), fVec3(1.0f), fVec3(-0.2f, -1.0f, -0.5f)),
          pointLight(fVec3(1.0f), fVec3(1.0f), fVec3(1.0f), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f),
          spotLight(fVec3(1.0), fVec3(1.0), fVec3(1.0f), fVec3(0.0f, -2.0f, 1.0f), fVec3(0.0f, 0.0f, -1.0f),
                    0.91f, 0.82f, 1.0f, 0.07f, 0.017f), dir(false), point(false), spot(false) {
//    auto particleProgram = std::make_shared<ShaderProgram>("particle");
//    auto texture = ResourceLoader::loadTexture("particle.png");
//    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    auto rect2 = std::make_shared<Rectangle>(10, 10, 120, 250);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        composite2->add(component);

        component = std::make_shared<UIButton>("Direct", 10, 70, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){dir = !dir;});
        composite2->add(component);

        component = std::make_shared<UIButton>("Point", 10, 130, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){point = !point;});
        composite2->add(component);

        component = std::make_shared<UIButton>("Spot", 10, 190, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){spot = !spot;});
        composite2->add(component);
    }

    rootComponent = composite2;

    model.enableBumpMapping(true);
    model.loadModel(ResourceLoader::getPath("sphere2.obj", MODEL));

    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    program = std::make_shared<ShaderProgram>("light");

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
    program->set3f("material.ambient", GOLD.ambient);
    program->set3f("material.diffuse", GOLD.diffuse);
    program->set3f("material.specular", GOLD.specular);
    program->set1f("material.shininess", GOLD.shininess);
    program->set3f("viewPos", camera.getPos());

    program->set1b("dir", dir);
    program->set1b("point", point);
    program->set1b("spot", spot);

    light(program.get(), "dirLight", dirLight);
    light(program.get(), "pointLight", pointLight);
    light(program.get(), "spotLight", spotLight);

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

const std::shared_ptr<LightStage> &LightStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<LightStage>(new LightStage);
    }

    return instance;
}

void LightStage::light(ShaderProgram *program, std::string name, DirectionalLight dirLight) {
    program->set3f(name+".direction", dirLight.getDirection());
    program->set3f(name+".ambient", dirLight.getAmbient());
    program->set3f(name+".diffuse", dirLight.getDiffuse());
    program->set3f(name+".specular", dirLight.getSpecular());
}

void LightStage::light(ShaderProgram *program, std::string name, PointLight pointLight) {
    program->set3f(name+".position", pointLight.getPosition());
    program->set1f(name+".constant", pointLight.getConstant());
    program->set1f(name+".linear", pointLight.getLinear());
    program->set1f(name+".quadratic", pointLight.getQuadratic());
    program->set3f(name+".ambient", pointLight.getAmbient());
    program->set3f(name+".diffuse", pointLight.getDiffuse());
    program->set3f(name+".specular", pointLight.getSpecular());
}

void LightStage::light(ShaderProgram *program, std::string name, SpotLight spotLight) {
    program->set3f(name+".position", spotLight.getPosition());
    program->set3f(name+".direction", spotLight.getDirection());
    program->set1f(name+".cutOff", spotLight.getCutOff());
    program->set1f(name+".outerCutOff", spotLight.getOuterCutOff());
    program->set1f(name+".constant", spotLight.getConstant());
    program->set1f(name+".linear", spotLight.getLinear());
    program->set1f(name+".quadratic", spotLight.getQuadratic());
    program->set3f(name+".ambient", spotLight.getAmbient());
    program->set3f(name+".diffuse", spotLight.getDiffuse());
    program->set3f(name+".specular", spotLight.getSpecular());
}
