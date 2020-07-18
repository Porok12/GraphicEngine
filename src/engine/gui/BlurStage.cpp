#include "BlurStage.h"

std::shared_ptr<BlurStage> BlurStage::instance = nullptr;

BlurStage::BlurStage() : bloom() {

    auto rect2 = std::make_shared<Rectangle>(10, 10, 120, 250);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        composite2->add(component);

        component = std::make_shared<UIButton>("Reset", 10, 70, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){});
        //program = std::make_shared<ShaderProgram>("gaussian");
        composite2->add(component);

        component = std::make_shared<UIButton>("Normal", 10, 130, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){});
        composite2->add(component);

        component = std::make_shared<UIButton>("Spec", 10, 190, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){});
        composite2->add(component);
    }

    rootComponent = composite2;

    plane.enableBumpMapping(false);
    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    program = std::make_shared<ShaderProgram>("final_gaussian");
    textureID = ResourceLoader::loadTexture("grid.png");
}

void BlurStage::renderUI() {
    UIStage::renderUI();
}

void BlurStage::renderContent(Camera camera, double dt) {
    GLuint tex = bloom.apply(textureID);

    program->use();
    program->set3f("viewPos", camera.getPos());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    Mat4 view = camera.getViewMatrix();
    ModelRenderer::getInstance()->setView(view);
    Mat4 mm = Mat4::identity();
    mm = Mat4::rotationX(-90.f) * Mat4::translate(0, 0, -8) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<BlurStage> &BlurStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<BlurStage>(new BlurStage);
    }

    return instance;
}