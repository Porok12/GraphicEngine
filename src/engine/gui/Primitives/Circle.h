#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
public:
    float radius;
    float resolution;

    Circle(float x, float y, float radius, float resolution = 1.0f)
            : Shape(x, y), radius(radius), resolution(resolution) {

    }

    bool contains(const double &x, const double &y) override {
        return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= radius * radius;
    }

    fVec4 getTextBox() override {
        return fVec4(x-radius, y-radius, x+radius, y+radius);
    }
};

#endif // CIRCLE_H