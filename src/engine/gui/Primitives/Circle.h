#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
public:
    float radius;

    Circle(float x, float y, float radius)
            : Shape(x, y), radius(radius) {

    }

    bool contains(const double &x, const double &y) override {
        return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= radius * radius;
    }
};

#endif // CIRCLE_H