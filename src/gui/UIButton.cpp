#include <engine/gui/UIButton.h>

void UIButton::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}


void UIButton::addCursorCallback(std::function<void(UIButton*)> &onCoursor) {
    this->onCursor = onCoursor;
}

void UIButton::draw() {
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)->setOffset(fVec3(getOffset().x, getOffset().y, 0))->render(shape);
    FontRenderer::getInstance()->setPosition(shape->x+getOffset().x, shape->y+getOffset().y)
            .setScale(0.5f)
            .setTextBox(shape->getTextBox())
            .render(text);
};

bool UIButton::click(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onClick) {
            onClick();
        }
        return true;
    }

    return false;
}

void UIButton::cursor(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onCursor) {
            onCursor(this);
        }
        this->backgroundColor = fVec3(0.8f);
    } else {
        this->backgroundColor = fVec3(0.5f);
    }
}

void UIButton::setBackgroundColor(const fVec3 &backgroundColor) {
    UIButton::backgroundColor = backgroundColor;
}
