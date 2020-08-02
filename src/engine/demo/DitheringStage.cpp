#include "DitheringStage.h"

std::shared_ptr<DitheringStage> DitheringStage::instance = nullptr;

DitheringStage::DitheringStage()
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

        component = std::make_shared<UISelectBox>(10, 70, 50, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"2x2", "4x4", "8x8"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int i){
            size = i;
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(4))->setY(new FixedConstraint(10)));
        composite2->add(component);

        component = std::make_shared<UISelectBox>(10, 80, 50, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"2", "4", "8", "16", "32", "64"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int i){
            paletteColors = i;
            palette.clear();

            switch (paletteId) {
                case 0: {
                    MedianCut medianCut;
                    medianCut.getPalette((i+1), palette, colors);
                    break;
                }
                case 1: {
                    switch (i) {
                        case 0: FixedPalette::getFixed(2, this->palette); break;
                        case 1: FixedPalette::getFixed(4, this->palette); break;
                        case 2: FixedPalette::getFixed(8, this->palette); break;
                        case 3: FixedPalette::getFixed(16, this->palette); break;
                        case 4: FixedPalette::getFixed(32, this->palette); break;
                        case 5: FixedPalette::getFixed(64, this->palette); break;
                    }
                    break;
                }
                case 2: {
                    switch (i) {
                        case 0: FixedPalette::getRandom(2, this->palette); break;
                        case 1: FixedPalette::getRandom(4, this->palette); break;
                        case 2: FixedPalette::getRandom(8, this->palette); break;
                        case 3: FixedPalette::getRandom(16, this->palette); break;
                        case 4: FixedPalette::getRandom(32, this->palette); break;
                        case 5: FixedPalette::getRandom(64, this->palette); break;
                    }
                    break;
                }
            }
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(60))->setY(new FixedConstraint(10)));
        composite2->add(component);

        component = std::make_shared<UISelectBox>(10, 150, 130, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"Dedicated", "Fixed", "Random"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int i){
            paletteId = i;
            palette.clear();
            switch (i) {
                case 0: {
                    MedianCut medianCut;
                    medianCut.getPalette((paletteColors+1), palette, colors);
                    break;
                }
                case 1: {
                    switch (paletteColors) {
                        case 0: FixedPalette::getFixed(2, this->palette); break;
                        case 1: FixedPalette::getFixed(4, this->palette); break;
                        case 2: FixedPalette::getFixed(8, this->palette); break;
                        case 3: FixedPalette::getFixed(16, this->palette); break;
                        case 4: FixedPalette::getFixed(32, this->palette); break;
                        case 5: FixedPalette::getFixed(64, this->palette); break;
                    }
                    break;
                }
                case 2: {
                    switch (paletteColors) {
                        case 0: FixedPalette::getRandom(2, this->palette); break;
                        case 1: FixedPalette::getRandom(4, this->palette); break;
                        case 2: FixedPalette::getRandom(8, this->palette); break;
                        case 3: FixedPalette::getRandom(16, this->palette); break;
                        case 4: FixedPalette::getRandom(32, this->palette); break;
                        case 5: FixedPalette::getRandom(64, this->palette); break;
                    }
                    break;
                }
            }
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(115))->setY(new FixedConstraint(10)));
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
        for (int i = 0; i < width*height*3; i += 3) {
            colors.push_back(fVec3((int)data[i+0], (int)data[i+1], (int)data[i+2]));
        }

        MedianCut medianCut;
        medianCut.getPalette(1, palette, colors);

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

    InputHandler::addDropListener([this](const char *path){
        int width, height, nrComponents;
        unsigned char * data = SOIL_load_image(path, &width, &height, &nrComponents, 0);

        if (data) {
            colors.clear();
            for (int i = 0; i < width*height*3; i += 3) {
                colors.push_back(fVec3((int)data[i+0], (int)data[i+1], (int)data[i+2]));
            }

            palette.clear();
            switch (paletteId) {
                case 0: {
                    MedianCut medianCut;
                    medianCut.getPalette((paletteColors+1), palette, colors);
                    break;
                }
                case 1: {
                    switch (paletteColors) {
                        case 0: FixedPalette::getFixed(2, this->palette); break;
                        case 1: FixedPalette::getFixed(4, this->palette); break;
                        case 2: FixedPalette::getFixed(8, this->palette); break;
                        case 3: FixedPalette::getFixed(16, this->palette); break;
                        case 4: FixedPalette::getFixed(32, this->palette); break;
                        case 5: FixedPalette::getFixed(64, this->palette); break;
                    }
                    break;
                }
                case 2: {
                    switch (paletteColors) {
                        case 0: FixedPalette::getRandom(2, this->palette); break;
                        case 1: FixedPalette::getRandom(4, this->palette); break;
                        case 2: FixedPalette::getRandom(8, this->palette); break;
                        case 3: FixedPalette::getRandom(16, this->palette); break;
                        case 4: FixedPalette::getRandom(32, this->palette); break;
                        case 5: FixedPalette::getRandom(64, this->palette); break;
                    }
                    break;
                }
            }

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
    });
}

void DitheringStage::renderUI() {
    UIStage::renderUI();
}

void DitheringStage::renderContent(FreeCamera &camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    ModelRenderer::getInstance()->setView(view);
    
    program->use();
    program->set3f("viewPos", camera.getPos());
    std::array<GLfloat, MAX_PALETTE*3> palette {};

    for (int i = 0; i < this->palette.size(); ++i) {
        palette[i*3+0] = this->palette[i].x / 255;
        palette[i*3+1] = this->palette[i].y / 255;
        palette[i*3+2] = this->palette[i].z / 255;
    }

    program->set1i("paletteSize", this->palette.size());
    program->set1i("size", size);
    glUniform3fv(glGetUniformLocation(program->getId(), "palette"), palette.size(), palette.data());

    

    glBindTexture(GL_TEXTURE_2D, textureID);


    Mat4 mm = Mat4::identity();
    mm = Mat4::rotationX(-90) * Mat4::translate(0, 0, -8) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<DitheringStage> &DitheringStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<DitheringStage>(new DitheringStage);
    }

    return instance;
}
