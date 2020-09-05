#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <bits/unique_ptr.h>

class RectangleConstraint {
public:
    virtual float get(float pPos, float pSize, float pos, float size) = 0;
};

class CenterConstraint : public RectangleConstraint {
public:
    float get(float pPos, float pSize, float pos, float size) override;
};

class FixedConstraint : public RectangleConstraint {
private:
    float pos = 0;
public:
    explicit FixedConstraint(float pos);

    float get(float pPos, float pSize, float pos, float size) override;
};

class FixedConstraint2 : public RectangleConstraint {
private:
    float pos = 0;
public:
    explicit FixedConstraint2(float pos);

    float get(float pPos, float pSize, float pos, float size) override;
};

class RelativeConstraint : public RectangleConstraint {
private:
    float aspect = 1;
public:
    explicit RelativeConstraint(float aspect);

    float get(float pPos, float pSize, float pos, float size) override;
};

//class AspectConstraint : public RectangleConstraint {
//    float aspect = 1;
//public:
//    explicit AspectConstraint(float aspect);
//
//    float get(float pPos, float pSize, float pos, float size) override;
//};

class RectangleConstraints {
private:
    std::unique_ptr<RectangleConstraint> x, y, w, h;
public:
//    explicit RectangleConstraints() {
//
//    }

    RectangleConstraints* setX(RectangleConstraint *x) {
        this->x = std::unique_ptr<RectangleConstraint>(x);
        return this;
    }

    RectangleConstraints* setY(RectangleConstraint *y) {
        this->y = std::unique_ptr<RectangleConstraint>(y);
        return this;
    }

    RectangleConstraints* setW(RectangleConstraint *w) {
        this->w = std::unique_ptr<RectangleConstraint>(w);
        return this;
    }

    RectangleConstraints* setH(RectangleConstraint *h) {
        this->h = std::unique_ptr<RectangleConstraint>(h);
        return this;
    }

    float getW(float pX, float pWidth, float x, float width) {
        return this->w->get(pX, pWidth, x, width);
    }

    float getH(float pY, float pHeight, float y, float height) {
        return this->h->get(pY, pHeight, y, height);
    }

    float getX(float pX, float pWidth, float x, float width) {
        return this->x->get(pX, pWidth, x, width);
    }

    float getY(float pY, float pHeight, float y, float height) {
        return pHeight - height - this->y->get(pY, pHeight, y, height);
    }
};

#endif // CONSTRAINT_H
