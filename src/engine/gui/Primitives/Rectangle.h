#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
    int x, y;
    int w, h;

    Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {

    }
};

#endif // RECTANGLE_H