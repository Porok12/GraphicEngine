#ifndef UISLIDER_H
#define UISLIDER_H

#include <memory>
#include <functional>
#include "UIComponent.h"

class UISlider : public UIComponent {
private:
    std::shared_ptr<Shape> slider;
    std::function<void ()> onClick;
    std::function<void(UISlider*)> onCursor;
    float max, min, current;
public:
    UISlider(const std::shared_ptr<Shape> &shape);

    void addClickCallback(std::function<void()> onClick);
    void addCursorCallback(std::function<void(UISlider*)> onCoursor);
};

#endif // UISLIDER_H