#include "UIStageManager.h"

UIStageManager::UIStageManager()
        : rootUI(), camera(fVec3(0)) {
    MenuStage::getInstance()->setXxx([this](){this->setStage(Stages::MESH);});
    MenuStage::getInstance()->setYyy([this](){this->setStage(Stages::PARTICLES);});
    MenuStage::getInstance()->setZzz([this](){this->setStage(Stages::LIGHT);});

    MeshStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    ParticleStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    LightStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
}

void UIStageManager::setStage(Stages stage) {
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
    }
}

void UIStageManager::render() {
    if (rootUI) {
        rootUI->renderContent(camera, deltaTime);
        rootUI->renderUI();
    }
}

void UIStageManager::update(Camera camera, double dt) {
    this->camera = camera;
    this->deltaTime = dt;
}

void UIStageManager::click(const double &x, const double &y) {
    if (!camera.isEnabled()) {
        rootUI->click(x, y);
    }
}

void UIStageManager::cursor(const double &x, const double &y) {
    if (!camera.isEnabled()) {
        rootUI->cursor(x, y);
    }
}
