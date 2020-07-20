#ifndef UISLIDER_H
#define UISLIDER_H

#include <gui/Primitives/Rectangle.h>
#include <gui/Primitives/PrimitiveRenderer.h>
#include <core/text/FontRenderer.h>
#include <math/Vec3.h>
#include <functional>
#include <memory>
#include <utility>
#include "UIComponent.h"

class UISlider : public UIComponent {
private:
    fVec3 backgroundColor;
    std::function<void ()> onClick;
    std::function<void(UISlider*)> onCursor;

    std::shared_ptr<Shape> slider, range;

public:
    UISlider(const std::shared_ptr<Shape> &shape) : UIComponent(shape) {
        this->backgroundColor = fVec3(0.5f, 0.5f, 0.5f);
        slider = std::make_shared<Circle>(0, 0, 10);
        range = std::make_shared<Rectangle>(0, 0, 100, 10);
    }

    UISlider(const int &x, const int &y, const int &w, const int &h)
            : UISlider(std::make_shared<Rectangle>(x, y, w, h)) {
    }

    void addClickCallback(std::function<void()> onClick);
    void addCursorCallback(std::function<void(UISlider*)> &onCoursor);

    void draw() override;
    void click(const double &x, const double &y) override;
    void cursor(const double &x, const double &y) override;

    void setBackgroundColor(const fVec3 &backgroundColor);

};

#endif // UISLIDER_H