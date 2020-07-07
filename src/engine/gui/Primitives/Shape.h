#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    float x, y;

    Shape(float x, float y) : x(x), y(y) {}

    virtual bool contains(const double &x, const double &y) = 0;
};

#endif // SHAPE_H