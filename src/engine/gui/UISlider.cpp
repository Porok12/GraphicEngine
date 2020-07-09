#include "UISlider.h"
#include <utility>

UISlider::UISlider(const std::shared_ptr <Shape> &shape) : UIComponent(shape) {
    
}

void UISlider::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}

void UISlider::addCursorCallback(std::function<void(UISlider *)> onCoursor) {
    this->onCursor = std::move(onCoursor);
}
