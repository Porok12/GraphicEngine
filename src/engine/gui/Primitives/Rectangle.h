#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
//    int x, y;
    int w, h;

    Rectangle(int x, int y, int w, int h)
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
};

#endif // RECTANGLE_H