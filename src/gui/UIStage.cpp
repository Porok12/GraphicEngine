#include <engine/gui/UIStage.h>
#include <engine/gui/UIRenderer.h>

UIStage::UIStage() = default;

void UIStage::renderUI() {
    for (const auto &component: rootComponent) {
        GUIRenderer::getInstance()->render(component.get());
    }
}

void UIStage::click(const double &x, const double &y) {
    for (const auto &component: rootComponent) {
        component->click(x, y);
    }
}

void UIStage::cursor(const double &x, const double &y) {
    for (const auto &component: rootComponent) {
        component->cursor(x, y);
    }
}

void UIStage::addRoot(const std::shared_ptr<UIComponent> &component) {
    rootComponent.push_back(component);
}
