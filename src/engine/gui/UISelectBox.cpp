#include "UISelectBox.h"

void UISelectBox::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}

void UISelectBox::addCursorCallback(std::function<void(UISelectBox*)> &onCoursor) {
    this->onCursor = onCoursor;
}

void UISelectBox::draw() {
    PrimitiveRenderer::getInstance()
            ->setColor(backgroundColor)
            ->setOffset(fVec3(getOffset().x, getOffset().y, 0))
            ->render(shape);

    fVec2 offset = getOffset() + fVec2(shape->x, shape->y);
    for (const auto &btn: buttons) {
        btn->draw();
    }
};

void UISelectBox::click(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onClick) {
            onClick();
        }
    }
}

void UISelectBox::cursor(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onCursor) {
            onCursor(this);
        }
        this->backgroundColor = fVec3(1.0f);
    } else {
        this->backgroundColor = fVec3(0.5f);
    }
}

void UISelectBox::setBackgroundColor(const fVec3 &backgroundColor) {
    UISelectBox::backgroundColor = backgroundColor;
}
