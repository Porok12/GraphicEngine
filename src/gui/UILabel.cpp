#include "engine/gui/UILabel.h"

void UILabel::draw() {
    fVec2 offset = getOffset() + fVec2(shape->x, shape->y);
    if(color) FontRenderer::getInstance()->setColor(*color);
    FontRenderer::getInstance()->setPosition((float)offset.x, (float)offset.y)
            .setScale(0.5f)
            .setTextBox(shape->getTextBox())
            .render(text);
    FontRenderer::getInstance()->setColor(iVec3(255, 255, 255));
}

void UILabel::setText(const std::string &text) {
    UILabel::text = text;
}

bool UILabel::click(const double &x, const double &y) {
    return false;
}

void UILabel::cursor(const double &x, const double &y) {

}

void UILabel::setColor(const iVec3 c) {
    if (!color) color.reset(new iVec3());
    *color = c;
}
