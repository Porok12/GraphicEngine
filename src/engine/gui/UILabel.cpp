#include "UILabel.h"

void UILabel::draw() {
    fVec2 offset = getOffset() + fVec2(shape->x, shape->y);
    FontRenderer::getInstance()->setPosition((float)offset.x, (float)offset.y)
            .setScale(0.5f)
            .setTextBox(shape->getTextBox())
            .render(text);
}

void UILabel::setText(const std::string &text) {
    UILabel::text = text;
}

bool UILabel::click(const double &x, const double &y) {
    return false;
}

void UILabel::cursor(const double &x, const double &y) {

}
