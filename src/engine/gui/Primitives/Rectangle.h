#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
    float w, h;

    Rectangle(float x, float y, float w, float h)
            : Shape(x, y), w(w), h(h) {

    }

    bool contains(const double &x, const double &y) override {
        if (x >= this->x && x <= this->x + this->w) {
            if (y >= this->y && y <= this->y + this->h) {
                return true;
            }
        }
        return false;
    }

    fVec4 getTextBox() override {
        return fVec4(x, y, x+w, y+h);
    }
};

#endif // RECTANGLE_H