#include "TextureStage.h"

std::shared_ptr<TextureStage> TextureStage::instance = nullptr;

TextureStage::TextureStage()
        : dirLight(fVec3(0.02), fVec3(1), fVec3(1), fVec3(-0.2f, -1.0f, -0.5f)), //dirLight(fVec3(0.05), fVec3(0.5), fVec3(0.8f), fVec3(-0.2f, -1.0f, -0.5f)),
          pointLight(fVec3(0.1), fVec3(1), fVec3(1), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f) {

    auto rect2 = std::make_shared<Rectangle>(10, 10, 120, 250);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        composite2->add(component);

        component = std::make_shared<UIButton>("Reset", 10, 70, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){program = std::make_shared<ShaderProgram>("texture");});
        composite2->add(component);

        component = std::make_shared<UIButton>("Normal", 10, 130, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){enableNormalMap = !enableNormalMap;});
        composite2->add(component);

        component = std::make_shared<UIButton>("Spec", 10, 190, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){enableSpecularMap = !enableSpecularMap;});
        composite2->add(component);
    }

    rootComponent = composite2;

    model.enableBumpMapping(true);
    model.loadModel(ResourceLoader::getPath("sphere3.obj", MODEL));

    plane.enableBumpMapping(true);
    plane.loadModel(ResourceLoader::getPath("untitled.obj", MODEL));

    program = std::make_shared<ShaderProgram>("texture");
}

void TextureStage::renderUI() {
    UIStage::renderUI();
}

void TextureStage::renderContent(Camera camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 0, -4) * mm;
    ModelRenderer::getInstance()->setModel( Mat4::rotation(a++, fVec3(0.9, 0.6, 0.3)) * mm);
    ModelRenderer::getInstance()->setView(view);


    
    program->use();
    program->set3f("viewPos", camera.getPos());
    program->set1b("enableNormalMap", enableNormalMap);
    program->set1b("enableSpecularMap", enableSpecularMap);

    light(program.get(), "dirLight", dirLight);
    pointLight.setPosition(fVec3(3*std::cos(b), -1, -4+3*std::sin(b))); b += dt;
    light(program.get(), "pointLight", pointLight);

    ModelRenderer::getInstance()->render(model, *program);

    mm = Mat4::identity();
    mm = Mat4::translate(0, -2, -4) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<TextureStage> &TextureStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<TextureStage>(new TextureStage);
    }

    return instance;
}

void TextureStage::light(ShaderProgram *program, std::string name, DirectionalLight dirLight) {
    program->set3f(name+".direction", dirLight.getDirection());
    program->set3f(name+".ambient", dirLight.getAmbient());
    program->set3f(name+".diffuse", dirLight.getDiffuse());
    program->set3f(name+".specular", dirLight.getSpecular());
}

void TextureStage::light(ShaderProgram *program, std::string name, PointLight pointLight) {
    program->set3f(name+".position", pointLight.getPosition());
    program->set1f(name+".constant", pointLight.getConstant());
    program->set1f(name+".linear", pointLight.getLinear());
    program->set1f(name+".quadratic", pointLight.getQuadratic());
    program->set3f(name+".ambient", pointLight.getAmbient());
    program->set3f(name+".diffuse", pointLight.getDiffuse());
    program->set3f(name+".specular", pointLight.getSpecular());
}
