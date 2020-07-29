#include "UIStage.h"

UIStage::UIStage() = default;

void UIStage::renderUI() {
    if (rootComponent) {
        GUIRenderer::getInstance()->render(rootComponent.get());
    }
}

void UIStage::click(const double &x, const double &y) {
    rootComponent->click(x, y);
}

void UIStage::cursor(const double &x, const double &y) {
    rootComponent->cursor(x, y);
}