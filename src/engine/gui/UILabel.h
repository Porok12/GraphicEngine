#ifndef UILABEL_H
#define UILABEL_H

#include "UIComponent.h"
#include <core/text/FontRenderer.h>
#include <memory>
#include <gui/Primitives/Rectangle.h>

class UILabel : public UIComponent {
private:
    std::string text;
public:
//    UILabel(const std::shared_ptr <Shape> &shape) : UIComponent(shape) {
//
//    }

    UILabel(std::string text, int x, int y)
            : UIComponent(std::make_shared<Rectangle>(x, y, 0, 0)) {
        this->text = text;
    }

    void draw() override;

    void click(const double &x, const double &y) override;

    void cursor(const double &x, const double &y) override;

    void setText(const std::string &text);
};

#endif // UILABEL_H