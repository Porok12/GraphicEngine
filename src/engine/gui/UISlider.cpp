#include "UISlider.h"

void UISlider::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}

void UISlider::addCursorCallback(std::function<void(UISlider*)> &onCoursor) {
    this->onCursor = onCoursor;
}

void UISlider::draw() {
    fVec2 offset = getOffset() + fVec2(shape->x, shape->y);
    fVec2 offset1 = offset + fVec2(0, shape->h / 2);
    fVec2 offset2 = offset + fVec2(0, shape->h / 2 - range->h / 2);
    PrimitiveRenderer::getInstance()->setColor(fVec3(0.5))
            ->setOffset(fVec3(offset2.x, offset2.y, 0))->render(range);
    PrimitiveRenderer::getInstance()->setColor(backgroundColor)
            ->setOffset(fVec3(offset1.x, offset1.y, 0))->render(slider);
};

bool UISlider::click(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onClick) {
            onClick();
        }

        if (slider->contains(x, y)) {
            action = true;
        }

        updateSlider(x);

        return true;
    }

    return false;
}

void UISlider::cursor(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if (action) {
            updateSlider(x);
        }

        if(onCursor) {
            onCursor(this);
        }
        this->backgroundColor = fVec3(1.0f);
    } else {
        this->backgroundColor = fVec3(0.5f);

        if (action) {
            if (x > shape->w) {
                slider->x = shape->w;
                onChange(rBorder);
            }

            if (x < shape->x) {
                onChange(lBorder);
            }
        }
    }
}

void UISlider::setBackgroundColor(const fVec3 &backgroundColor) {
    UISlider::backgroundColor = backgroundColor;
}

void UISlider::addChangedCallback(std::function<void(float)> onChange) {
    this->onChange = onChange;
}

void UISlider::setValue(float value) {
    float f = (value - lBorder) / (rBorder - lBorder);
    slider->x = f * range->w;
}

void UISlider::updateSlider(double x) {
    float pixStep = range->w / (rBorder - lBorder);
    float xPos = (float) x - shape->x;

    if (std::abs(slider->x - xPos) >= step * pixStep) {
        float diff = (int) xPos % (int) (step * pixStep);
        slider->x = xPos - diff;
        if (onChange) {
            float f = slider->x / range->w;
            onChange(lBorder + (rBorder - lBorder) * f);
        }
    }
}
