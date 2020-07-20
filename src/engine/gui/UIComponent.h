#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <memory>
#include <gui/Primitives/Shape.h>
#include <math/Vec2.h>
#include <gui/Utils/Utils.h>

class UIComponent : public std::enable_shared_from_this<UIComponent> {
protected:
    std::shared_ptr<Shape> shape;
    std::weak_ptr<UIComponent> parent;

//    virtual std::shared_ptr<UIComponent> shared_from_this() {
//        std::cerr << std::enable_shared_from_this<UIComponent>::shared_from_this().use_count() << std::endl;
//        return std::enable_shared_from_this<UIComponent>::shared_from_this();
//    }
public:
    UIComponent(const std::shared_ptr<Shape> &shape) : shape(shape) { };
    virtual ~UIComponent() { }

    virtual void click(const double &x, const double &y) = 0;
    virtual void cursor(const double &x, const double &y) = 0;
    virtual void draw() = 0;

//    void setParent(const std::weak_ptr<UIComponent> &parent) {
//        UIComponent::parent = parent;
//    }

//    std::shared_ptr<UIComponent> getPointer() {
//        return shared_from_this();
//    }

    void setParent(const std::shared_ptr<UIComponent> &parent) {
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
