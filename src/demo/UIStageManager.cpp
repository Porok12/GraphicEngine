#include "UIStageManager.h"

UIStageManager::UIStageManager(const std::shared_ptr<FreeCamera> &camera)
        : rootUI() {
    MenuStage::getInstance()->setXxx([this](){this->setStage(Stages::MESH);});
    MenuStage::getInstance()->setYyy([this](){this->setStage(Stages::PARTICLES);});
    MenuStage::getInstance()->setZzz([this](){this->setStage(Stages::SHADING);});
    MenuStage::getInstance()->setAaa([this](){this->setStage(Stages::LIGHT);});
    MenuStage::getInstance()->setBbb([this](){this->setStage(Stages::TEXTURE_MAPS);});
    MenuStage::getInstance()->setDdd([this](){this->setStage(Stages::BLUR);});
    MenuStage::getInstance()->setCcc([this](){this->setStage(Stages::DITHERING);});
    MenuStage::getInstance()->setEee([this](){this->setStage(Stages::BRESENHAM);});
    MenuStage::getInstance()->setFff([this](){this->setStage(Stages::SIERPINSKI);});
    MenuStage::getInstance()->setGgg([this](std::string text){if(text=="Aga")this->setStage(Stages::COMBO);});
    MenuStage::getInstance()->setHhh([this](){this->setStage(Stages::COMBO);});

    MeshStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    ParticleStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    LightStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    ShadingStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    TextureStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    BlurStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    DitheringStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    BresenhamStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    SierpinskiStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    ComboStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});

    this->camera = camera;
}

void UIStageManager::setStage(Stages stage) {
    BresenhamStage::getInstance()->setFocus(Stages::BRESENHAM == stage);

    switch (stage) {
        case MENU:
            rootUI = MenuStage::getInstance();
            break;
        case MESH:
            rootUI = MeshStage::getInstance();
            break;
        case PARTICLES:
            rootUI = ParticleStage::getInstance();
            break;
        case LIGHT:
            rootUI = LightStage::getInstance();
            break;
        case SHADING:
            rootUI = ShadingStage::getInstance();
            break;
        case TEXTURE_MAPS:
            rootUI = TextureStage::getInstance();
            break;
        case BLUR:
            rootUI = BlurStage::getInstance();
            break;
        case DITHERING:
            rootUI = DitheringStage::getInstance();
            break;
        case BRESENHAM:
            rootUI = BresenhamStage::getInstance();
            break;
        case SIERPINSKI:
            rootUI = SierpinskiStage::getInstance();
            break;
        case COMBO:
            rootUI = ComboStage::getInstance();
            break;
    }

    GUIRenderer::getInstance()->requestUpdate();
    camera->reset();
}

void UIStageManager::render() {
    if (rootUI) {
        glEnable(GL_DEPTH_TEST);
        rootUI->renderContent(*camera, deltaTime);
        glDisable(GL_DEPTH_TEST);

        if (!disabled) {
            rootUI->renderUI();
        }
    }
}

void UIStageManager::update(double dt) {
    this->deltaTime = dt;
}

void UIStageManager::click(const double &x, const double &y) {
    if (!disabled) {
        rootUI->click(x, y);
    }
}

void UIStageManager::cursor(const double &x, const double &y) {
    if (!disabled) {
        rootUI->cursor(x, y);
    }
}

void UIStageManager::setDisabled(bool disabled) {
    UIStageManager::disabled = disabled;
}

bool UIStageManager::isDisabled() const {
    return disabled;
}
