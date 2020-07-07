#include <iostream>
#include "UIComposite.h"

UIComposite::UIComposite(const std::shared_ptr<Shape> &shape) : UIComponent(shape), children() {

}

void UIComposite::add(std::shared_ptr<UIComponent> &child) {
    this->children.push_back(child);
}

//bool UIComposite::remove(std::shared_ptr<UIComponent> &child) {
//    return false;
//}

std::vector<std::shared_ptr<UIComponent>>& UIComposite::getChildren() {
    return children;
}

void UIComposite::draw(float offsetX, float offsetY) {
    for(const auto &ch: children) {
        ch->draw(0, 0);
    }
}

