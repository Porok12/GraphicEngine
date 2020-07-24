#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <memory>
#include <gui/Primitives/Shape.h>
#include <math/Vec2.h>
#include <gui/Utils/Utils.h>
#include "gui/Utils/Constraint.h"

class UIComponent : public std::enable_shared_from_this<UIComponent> {
private:
    std::unique_ptr<RectangleConstraints> constraints;
protected:
    std::shared_ptr<Shape> shape;
    std::weak_ptr<UIComponent> parent;

//    virtual std::shared_ptr<UIComponent> shared_from_this() {
//        std::cerr << std::enable_shared_from_this<UIComponent>::shared_from_this().use_count() << std::endl;
//        return std::enable_shared_from_this<UIComponent>::shared_from_this();
//    }
public:
    UIComponent(const std::shared_ptr<Shape> &shape)
            : shape(shape), constraints(new RectangleConstraints) {
        constraints->setX(new FixedConstraint(0));
        constraints->setY(new FixedConstraint(0));
        constraints->setW(new FixedConstraint2(shape->w));
        constraints->setH(new FixedConstraint2(shape->h));
    };

    virtual ~UIComponent() { }

    virtual bool click(const double &x, const double &y) = 0;
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

    virtual void update(int w, int h) {
        if (parent.use_count() == 0) {
//            shape->w = w;
//            shape->h = h;
            shape->w = constraints->getW(0, w, shape->x, shape->w);
            shape->h = constraints->getH(0, h, shape->y, shape->h);
        } else {
            auto p = parent.lock();
            shape->x = constraints->getX(p->shape->x, p->shape->w, shape->x, shape->w);
            shape->y = constraints->getY(p->shape->h, p->shape->h, shape->y, shape->h);
//            shape->w = constraints.getW(p->shape->x, p->shape->w, shape->w);
//            shape->h = constraints.getH(p->shape->h, p->shape->h, shape->h);
        }
    }

    void setConstraints(RectangleConstraints *constraints) {
        this->constraints.reset(constraints);
    }
};

#endif // UICOMPONENT_H
