#include "UITextBox.h"

UITextBox::UITextBox(const std::shared_ptr<Shape> &shape) : UIComponent(shape) {
    InputHandler::addCharactersListener([this](const unsigned int& character){
        if (active && text.size() < maxSize) {
            std::string s(1, character);
            char const *pchar = s.c_str();
            text.append(pchar);
        }
    });

    InputHandler::addKeyPressedListener([this](const int& key){
        if (active) {
            if (key == GLFW_KEY_BACKSPACE) {
                if (!text.empty()) {
                    text.pop_back();
                }
            }
        }
    });
}

UITextBox::UITextBox(int x, int y, int w, int h)
    : UITextBox(std::make_shared<Rectangle>(x, y, w, h)) {

}

void UITextBox::click(const double &x, const double &y) {
    active = false;
    
    if (shape->contains(x, y)) {
        active = true;
    }

    backgroundColor = active ? fVec3(1.0) : fVec3(0.5);
}

void UITextBox::cursor(const double &x, const double &y) {
    if (shape->contains(x, y)) {

    }
}

void UITextBox::draw() {
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)->setOffset(fVec3(getOffset().x, getOffset().y, 0))->render(shape);
    FontRenderer::getInstance()->setPosition(shape->x+getOffset().x, shape->y+getOffset().y)
            .setScale(0.5f)
            .setTextBox(shape->getTextBox())
            .render(text);
}
