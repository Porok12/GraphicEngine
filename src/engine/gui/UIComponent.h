#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <memory>
#include <gui/Primitives/Shape.h>

class UIComponent {
protected:
    std::shared_ptr<Shape> shape;
public:
    UIComponent(const std::shared_ptr<Shape> &shape) : shape(shape) { };

    virtual void click(const double &x, const double &y) = 0;
    virtual void cursor(const double &x, const double &y) = 0;
    virtual void draw(float offsetX, float offsetY) = 0;

    const std::shared_ptr<Shape> &getShape() const {
        return shape;
    }
};

#endif // UICOMPONENT_H
