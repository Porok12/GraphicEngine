#include "UIStageManager.h"

UIStageManager::UIStageManager()
        : rootUI(), camera(fVec3(0)) {
//    MenuStage::getInstance()->setXxx([this](){this->setStage(Stages::MENU);});
    std::dynamic_pointer_cast<MenuStage>(MenuStage::getInstance())->setXxx([this](){std::cout <<"!!\n";this->setStage(Stages::MESH);});
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
            break;
    }
}

void UIStageManager::render() {
    if (rootUI) {
        rootUI->renderUI();
        rootUI->renderContent(camera, deltaTime);
    }
}

void UIStageManager::update(Camera camera, double dt) {
    this->camera = camera;
    this->deltaTime = dt;
}

void UIStageManager::click(const double &x, const double &y) {
    rootUI->click(x, y);
}

void UIStageManager::cursor(const double &x, const double &y) {
    rootUI->cursor(x, y);
}
