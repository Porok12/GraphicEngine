#ifndef UISLIDER_H
#define UISLIDER_H

#include <gui/Primitives/Rectangle.h>
#include <gui/Primitives/PrimitiveRenderer.h>
#include <core/text/FontRenderer.h>
#include <math/Vec3.h>
#include <functional>
#include <memory>
#include <utility>
#include <core/InputHandler.h>
#include "UIComponent.h"

class UISlider : public UIComponent {
private:
    bool action = false;
    fVec3 backgroundColor;
    std::function<void ()> onClick;
    std::function<void (float)> onChange;
    std::function<void(UISlider*)> onCursor;

    std::shared_ptr<Shape> slider, range;
    float lBorder = 0, rBorder = 10, step = 2;

    void updateSlider(double x);

public:
    UISlider(const std::shared_ptr<Shape> &shape) : UIComponent(shape) {
        this->backgroundColor = fVec3(0.5f, 0.5f, 0.5f);
        slider = std::make_shared<Circle>(0, 0, 10);
        range = std::make_shared<Rectangle>(0, 0, 100, 10);

        InputHandler::addMouseReleaseListner([this](const double &x, const double &y){
            action = false;
        });
        InputHandler::addMouseButtonListner([this](const double &x, const double &y){
            if (this->shape->contains(x, y)) {
                action = true;
            }
        });
    }

    UISlider(const int &x, const int &y, const int &w, const int &h)
            : UISlider(std::make_shared<Rectangle>(x, y, w, h)) {
    }

    UISlider(const int &x, const int &y, const int &w, const int &h, float l, float r, float s)
            : UISlider(std::make_shared<Rectangle>(x, y, w, h)) {
        this->lBorder = l;
        this->rBorder = r;
        this->step= s;
    }

    void addClickCallback(std::function<void()> onClick);
    void addCursorCallback(std::function<void(UISlider*)> &onCoursor);
    void addChangedCallback(std::function<void(float)> onChange);

    void draw() override;
    bool click(const double &x, const double &y) override;
    void cursor(const double &x, const double &y) override;

    void setBackgroundColor(const fVec3 &backgroundColor);
    void setValue(float value);

};

#endif // UISLIDER_H