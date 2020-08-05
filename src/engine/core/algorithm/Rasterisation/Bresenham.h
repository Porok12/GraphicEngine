#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <vector>
#include <math/Vec2.h>

class Bresenham {
    using point = iVec2;
private:
    void plotLineHigh(point p1, point p2, std::vector<point> &points);
    void plotLineLow(point p1, point p2, std::vector<point> &points);
public:
    std::vector<point> getLine(point p1, point p2);
    std::vector<point> getCircle(point p, double radius);
    std::vector<Bresenham::point> getElipse(Bresenham::point p, double a, double b);
};

#endif // BRESENHAM_H