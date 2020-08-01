#include "BresenhamStage.h"

std::shared_ptr<BresenhamStage> BresenhamStage::instance = nullptr;

BresenhamStage::BresenhamStage()
        : dirLight(fVec3(0.02), fVec3(1), fVec3(1), fVec3(-0.2f, -1.0f, -0.5f)), //dirLight(fVec3(0.05), fVec3(0.5), fVec3(0.8f), fVec3(-0.2f, -1.0f, -0.5f)),
          pointLight(fVec3(0.1), fVec3(1), fVec3(1), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f) {

    auto rect2 = std::make_shared<Rectangle>(10, 10, 250, 500);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(500 - 50 - 10)));
        composite2->add(component);
    }

    composite2->update(800, 600);
    rootComponent = composite2;

    plane.enableBumpMapping(true);
    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    program = std::make_shared<ShaderProgram>("dithering");

    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char * data = SOIL_load_image(ResourceLoader::getPath("test.bmp", TEXTURE).c_str(),
            &width, &height, &nrComponents, 0);

    if (data) {
        GLenum format = GL_RED;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SOIL_free_image_data(data);
    }
}

void BresenhamStage::renderUI() {
    UIStage::renderUI();
}

void BresenhamStage::renderContent(FreeCamera camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    ModelRenderer::getInstance()->setView(view);
    
    program->use();
    program->set3f("viewPos", camera.getPos());
    glBindTexture(GL_TEXTURE_2D, textureID);


    Mat4 mm = Mat4::identity();
    mm = Mat4::rotationX(-90) * Mat4::translate(0, 0, -8) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<BresenhamStage> &BresenhamStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<BresenhamStage>(new BresenhamStage);
    }

    return instance;
}
