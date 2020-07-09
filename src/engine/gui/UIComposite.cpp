#include <iostream>
#include <algorithm>
#include "UIComposite.h"

UIComposite::UIComposite(const std::shared_ptr<Shape> &shape) : UIComponent(shape), children() {

}

void UIComposite::add(std::shared_ptr<UIComponent> &child) {
    this->children.push_back(child);
    child->setParent(weak_from_this());
}

void UIComposite::remove(std::shared_ptr<UIComponent> &child) {
    auto removed = children.erase(std::remove(children.begin(), children.end(), child), children.end());
//    children.erase(std::remove_if(children.begin(), children.end(), [](auto const& pi){ return *pi % 2 == 0; }), children.end());
}

std::vector<std::shared_ptr<UIComponent>>& UIComposite::getChildren() {
    return children;
}

void UIComposite::draw() {
    for(const auto &ch: children) {
        ch->draw();
    }
}

void UIComposite::click(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        for(const auto& ch: children) {
            ch->click(x, y);
        }
    }
}

void UIComposite::cursor(const double &x, const double &y) {
//    std::cout << shape->x << std::endl;
    if (shape->contains(x, y)) {
        for(const auto& ch: children) {
            ch->cursor(x-shape->x, y-shape->y);
//            ch->cursor(x, y);
        }
    }
}

