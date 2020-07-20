#include "UISlider.h"

void UISlider::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}

void UISlider::addCursorCallback(std::function<void(UISlider*)> &onCoursor) {
    this->onCursor = onCoursor;
}

void UISlider::draw() {
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)->setOffset(fVec3(getOffset().x, getOffset().y, 0))->render(shape);
    fVec2 offset = getOffset() + fVec2(shape->x, shape->y);
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)
            ->setOffset(fVec3(offset.x, offset.y, 0))->render(slider);
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)
            ->setOffset(fVec3(offset.x, offset.y, 0))->render(range);
};

void UISlider::click(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onClick) {
            onClick();
        }
    }
}

void UISlider::cursor(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onCursor) {
            onCursor(this);
        }
        this->backgroundColor = fVec3(1.0f);
    } else {
        this->backgroundColor = fVec3(0.5f);
    }
}

void UISlider::setBackgroundColor(const fVec3 &backgroundColor) {
    UISlider::backgroundColor = backgroundColor;
}
