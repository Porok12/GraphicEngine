#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <gui/Primitives/Rectangle.h>
#include <gui/Primitives/PrimitiveRenderer.h>
#include <core/text/FontRenderer.h>
#include <math/Vec3.h>
#include <functional>
#include <memory>
#include <utility>
#include "UIComponent.h"

class UIButton : public UIComponent {
private:
    std::function<void ()> onClick;
    std::function<void(UIButton*)> onCursor;

protected:
    std::string text = "Button";
    fVec3 backgroundColor;

public:
    UIButton(const std::shared_ptr<Shape> &shape) : UIComponent(shape) {
        this->backgroundColor = fVec3(0.5f, 0.5f, 0.5f);
    }

    UIButton(const int &x, const int &y, const int &w, const int &h)
            : UIButton(std::make_shared<Rectangle>(x, y, w, h)) {
    }

    UIButton(std::string text, const int &x, const int &y, const int &w, const int &h)
            : UIButton(std::make_shared<Rectangle>(x, y, w, h)) {
        this->text = std::move(text);
    }

    void addClickCallback(std::function<void()> onClick);
//    void addCursorCallback(std::function<void(UIButton*)> onCoursor);
    void addCursorCallback(std::function<void(UIButton*)> &onCoursor);

    void draw() override;
    void click(const double &x, const double &y) override;
    void cursor(const double &x, const double &y) override;

    void setBackgroundColor(const fVec3 &backgroundColor);

};

#endif // UIBUTTON_H