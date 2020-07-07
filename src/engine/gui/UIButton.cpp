#include "UIButton.h"
#include <utility>

void UIButton::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}

void UIButton::addCursorCallback(std::function<void(UIButton*)> onCoursor) {
    this->onCursor = std::move(onCoursor);
}

void UIButton::draw(float offsetX, float offsetY) {
    //TODO: Render text
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)->render(std::dynamic_pointer_cast<Rectangle>(shape).get());
    FontRenderer::getInstance()->setPosition(shape->x, shape->y).setScale(0.5f).render(text);
};

void UIButton::click(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onClick) {
            onClick();
        }
    }
}

void UIButton::cursor(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onCursor) {
            onCursor(this);
        }
        this->backgroundColor = fVec3(1.0f);
    } else {
        this->backgroundColor = fVec3(0.5f);
    }
}

void UIButton::setBackgroundColor(const fVec3 &backgroundColor) {
    UIButton::backgroundColor = backgroundColor;
}
