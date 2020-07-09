#include "UIButton.h"

void UIButton::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}

void UIButton::addCursorCallback(std::function<void(UIButton*)> onCoursor) {
    this->onCursor = std::move(onCoursor);
}

void UIButton::draw() {
//    std::cout << parent.use_count() << std::endl;

//    if (auto p = parent.lock()) {
//        //shape->x += p->getShape()->x;
//    }

    //TODO: Render text

//    std::cout << shape << std::endl;
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)->setOffset(fVec3(getOffset().x, getOffset().y, 0))->render(shape);
    FontRenderer::getInstance()->setPosition(shape->x+getOffset().x, shape->y+getOffset().y)
            .setScale(0.5f)
            .setMax(shape->endPoint().x-shape->x, shape->endPoint().y-shape->y)
            .render(text);
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
