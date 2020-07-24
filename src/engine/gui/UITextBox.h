#ifndef UITEXTBOX_H
#define UITEXTBOX_H

#include "UIComponent.h"
#include <gui/Primitives/Rectangle.h>
#include <gui/Primitives/PrimitiveRenderer.h>
#include <core/text/FontRenderer.h>
#include <core/InputHandler.h>

class UITextBox : public UIComponent {
private:
    bool active = false;
    int maxSize = 10;
    std::string text = "TextBox";
    fVec3 backgroundColor = fVec3(0.5f);
public:
    UITextBox(const std::shared_ptr<Shape> &shape);
    UITextBox(int x, int y, int w, int h);

    bool click(const double &x, const double &y) override;

    void cursor(const double &x, const double &y) override;

    void draw() override;
};

#endif // UITEXTBOX_H