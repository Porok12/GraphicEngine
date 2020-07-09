#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <memory>
#include <gui/Primitives/Shape.h>
#include <math/Vec2.h>

class UIComponent {
private:
//    fVec2 offset;

protected:
    std::shared_ptr<Shape> shape;
    std::weak_ptr<UIComponent> parent;

public:
    UIComponent(const std::shared_ptr<Shape> &shape) : shape(shape) { };

    virtual void click(const double &x, const double &y) = 0;
    virtual void cursor(const double &x, const double &y) = 0;
    virtual void draw() = 0;

    void setParent(const std::weak_ptr<UIComponent> &parent) {
        UIComponent::parent = parent;
    }

    const std::shared_ptr<Shape> &getShape() const {
        return shape;
    }

    fVec2 getOffset() {
        if (auto p = parent.lock()) {
            return p->getOffset() + fVec2(p->shape->x, p->shape->y);
        }

        return fVec2(0.0f);
    }
};

#endif // UICOMPONENT_H
