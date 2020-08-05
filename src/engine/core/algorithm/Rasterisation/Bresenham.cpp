#include "Bresenham.h"

std::vector<Bresenham::point> Bresenham::getLine(Bresenham::point p1, Bresenham::point p2) {
    std::vector<Bresenham::point> points;

    if (std::abs(p2.y - p1.y) < std::abs(p2.x - p1.x)) {
        if (p1.x > p2.x) {
            plotLineLow(Bresenham::point(p2.x, p2.y), Bresenham::point(p1.x, p1.y), points);
        } else {
            plotLineLow(Bresenham::point(p1.x, p1.y), Bresenham::point(p2.x, p2.y), points);
        }

    } else {
        if (p1.y > p2.y) {
            plotLineHigh(Bresenham::point(p2.x, p2.y), Bresenham::point(p1.x, p1.y), points);
        } else {
            plotLineHigh(Bresenham::point(p1.x, p1.y), Bresenham::point(p2.x, p2.y), points);
        }
    }

    return points;
}

void Bresenham::plotLineHigh(Bresenham::point p1, Bresenham::point p2, std::vector<point> &points) {
    auto d = p2 - p1;
    auto xi = 1.0;
    if (d.x < 0) {
        xi = -1.0;
        d.x = -d.x;
    }
    auto D = 2*d.x - d.y;
    auto x = p1.x;

    for (auto y = p1.y; y < p2.y; y += 1) {
        points.push_back(Bresenham::point(x, y));
        if (D > 0) {
            x = x + xi;
            D = D - 2*d.y;
        }
        D = D + 2*d.x;
    }
}

void Bresenham::plotLineLow(Bresenham::point p1, Bresenham::point p2, std::vector<point> &points) {
    auto d = p2 - p1;
    auto yi = 1.0;
    if (d.y < 0) {
        yi = -1.0;
        d.y = -d.y;
    }

    auto D = 2*d.y - d.x;
    auto y = p1.y;

    for (auto x = p1.x; x < p2.x; x += 1) {
        points.push_back(Bresenham::point(x, y));
        if (D > 0) {
            y = y + yi;
            D = D - 2*d.x;
        }
        D = D + 2*d.y;
    }
}

std::vector<Bresenham::point> Bresenham::getCircle(Bresenham::point p, double radius) {
    std::vector<Bresenham::point> points;

    auto f = static_cast<int>(1 - radius);
    int ddF_x = 0;
    auto ddF_y = static_cast<int>(-2 * radius);
    int x = 0;
    auto y = static_cast<int>(radius);

    points.emplace_back(p.x, p.y + radius);
    points.emplace_back(p.x, p.y - radius);
    points.emplace_back(p.x + radius, p.y);
    points.emplace_back(p.x - radius, p.y);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;
        points.emplace_back(p.x + x, p.y + y);
        points.emplace_back(p.x - x, p.y + y);
        points.emplace_back(p.x + x, p.y - y);
        points.emplace_back(p.x - x, p.y - y);
        points.emplace_back(p.x + y, p.y + x);
        points.emplace_back(p.x - y, p.y + x);
        points.emplace_back(p.x + y, p.y - x);
        points.emplace_back(p.x - y, p.y - x);
    }
    
    return points;
}

std::vector<Bresenham::point> Bresenham::getElipse(Bresenham::point p, double a, double b) {
    std::vector<Bresenham::point> points;

    if (a < 1 || b < 1) {
        return points;
    }

    int wx, wy;
    int thresh;
    auto asq = static_cast<int>(a * a);
    auto bsq = static_cast<int>(b * b);
    int xa, ya;

    points.emplace_back(p.x, p.y+b);
    points.emplace_back(p.x, p.y-b);

    wx = 0;
    wy = static_cast<int>(b);
    xa = 0;
    ya = static_cast<int>(asq * 2 * b);
    thresh = static_cast<int>(asq / 4 - asq * b);

    for (;;) {
        thresh += xa + bsq;

        if (thresh >= 0) {
            ya -= asq * 2;
            thresh -= ya;
            wy--;
        }

        xa += bsq * 2;
        wx++;

        if (xa >= ya)
            break;


        points.emplace_back(p.x+wx, p.y-wy);
        points.emplace_back(p.x-wx, p.y-wy);
        points.emplace_back(p.x+wx, p.y+wy);
        points.emplace_back(p.x-wx, p.y+wy);
    }

    points.emplace_back(p.x+a, p.y);
    points.emplace_back(p.x-a, p.y);

    wx = static_cast<int>(a);
    wy = 0;
    xa = static_cast<int>(bsq * 2 * a);

    ya = 0;
    thresh = static_cast<int>(bsq / 4 - bsq * a);

    for (;;) {
        thresh += ya + asq;

        if (thresh >= 0) {
            xa -= bsq * 2;
            thresh = thresh - xa;
            wx--;
        }

        ya += asq * 2;
        wy++;

        if (ya > xa)
            break;

        points.emplace_back(p.x+wx, p.y-wy);
        points.emplace_back(p.x-wx, p.y-wy);
        points.emplace_back(p.x+wx, p.y+wy);
        points.emplace_back(p.x-wx, p.y+wy);
    }
    
    return points;
}
