#include "DitheringStage.h"

std::shared_ptr<DitheringStage> DitheringStage::instance = nullptr;

DitheringStage::DitheringStage()
        : dirLight(fVec3(0.02), fVec3(1), fVec3(1), fVec3(-0.2f, -1.0f, -0.5f)), //dirLight(fVec3(0.05), fVec3(0.5), fVec3(0.8f), fVec3(-0.2f, -1.0f, -0.5f)),
          pointLight(fVec3(0.1), fVec3(1), fVec3(1), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f) {

    auto rect2 = std::make_shared<Rectangle>(10, 10, 120, 250);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        composite2->add(component);

        component = std::make_shared<UIButton>("Reset", 10, 70, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){program = std::make_shared<ShaderProgram>("dithering");});
        composite2->add(component);

        component = std::make_shared<UIButton>("Size", 10, 130, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){size=(size+1)%3;});
        composite2->add(component);

        component = std::make_shared<UIButton>("", 10, 190, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){});
        composite2->add(component);
    }

    rootComponent = composite2;

    plane.enableBumpMapping(true);
    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    program = std::make_shared<ShaderProgram>("dithering");

    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char * data = SOIL_load_image("/home/przemek/Desktop/SEM7/Praca/GraphicEngine/res/textures/test.bmp",
            &width, &height, &nrComponents, 0);

    if (data) {
        for (int i = 0; i < width*height*3; i += 3) {
            colors.push_back(fVec3((int)data[i+0], (int)data[i+1], (int)data[i+2]));
        }
        MedianCut medianCut;
        medianCut.getPalette(3, palette, colors);

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

void DitheringStage::renderUI() {
    UIStage::renderUI();
}

void DitheringStage::renderContent(Camera camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    ModelRenderer::getInstance()->setView(view);
    
    program->use();
    program->set3f("viewPos", camera.getPos());
    std::array<GLfloat, 8*3> palette = {
        0, 0, 0,
        0, 0, 1,
        0, 1, 0,
        0, 1, 1,
        1, 0, 0,
        1, 0, 1,
        1, 1, 0,
        1, 1, 1
    };

    for (int i = 0; i < 8; ++i) {
        palette[i*3+0] = this->palette[i].x / 255;
        palette[i*3+1] = this->palette[i].y / 255;
        palette[i*3+2] = this->palette[i].z / 255;
    }



    program->set1i("paletteSize", palette.size()/3);
    program->set1i("size", size);
    glUniform3fv(glGetUniformLocation(program->getId(), "palette"), 8*3, palette.data());

    

    glBindTexture(GL_TEXTURE_2D, textureID);


    Mat4 mm = Mat4::identity();
    mm = Mat4::rotationX(-90) * Mat4::translate(0, 0, -8) * mm;
    ModelRenderer::getInstance()->setModel(mm);
//    ModelRenderer::getInstance()->setProjection(Mat4::getOrtho(-4, 4, -4, 4, 0.1, 20));
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<DitheringStage> &DitheringStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<DitheringStage>(new DitheringStage);
    }

    return instance;
}
