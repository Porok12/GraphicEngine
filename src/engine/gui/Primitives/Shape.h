#ifndef SHAPE_H
#define SHAPE_H

#include <math/Vec3.h>

class Shape {
protected:
public:
//    fVec3 offset;
    float x, y;

    Shape(float x, float y) : x(x), y(y) {}

    virtual bool contains(const double &x, const double &y) = 0;
    virtual fVec3 endPoint() = 0;
};

#endif // SHAPE_H