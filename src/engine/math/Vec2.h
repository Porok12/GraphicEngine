#ifndef VEC2_H
#define VEC2_H

#include "Vector.h"

template <class type>
class Vec2 : public Vector<type, 2> {
public:
    Property<type> x, y;

    Vec2(Vector<type, 2> v);
    explicit Vec2(type x, type y);
    explicit Vec2(type xy);
    explicit Vec2();

//    Vec2& operator=(const Vec2& other) {
//        return Vector<type, 2>::operator=(other);
//    }
    Vec2& operator+=(const Vec2 &other) {
        Vector<type, 2>::operator+=(other);
        return *this;
    }
    Vec2& operator+=(type t) {
        Vector<type, 2>::operator+=(t);
        return *this;
    }
    Vec2 operator+(const Vec2 &other) const {
        return Vector<type, 2>::operator+(other);
    }
    Vec2 operator+(type t) const {
        return Vector<type, 2>::operator+(t);
    }
    Vec2& operator-=(const Vec2 &other) {
        Vector<type, 2>::operator-=(other);
        return *this;
    }
    Vec2& operator-=(type t) {
        Vector<type, 2>::operator-=(t);
        return *this;
    }
    Vec2 operator-(const Vec2 &other) const {
        return Vector<type, 2>::operator-(other);
    }
    Vec2 operator-(type t) const {
        return Vector<type, 2>::operator-(t);
    }
    Vec2& operator*=(const Vec2 &other) {
        Vector<type, 2>::operator*=(other);;
        return *this;
    };
    Vec2& operator*=(type t) {
        Vector<type, 2>::operator*=(t);
        return *this;
    };
    Vec2 operator*(const Vec2 &other) const {
        return Vector<type, 2>::operator*(other);
    };
    Vec2 operator*(type t) const {
        return Vector<type, 2>::operator*(t);
    };
};

// -----------------------------

// integer vector

class iVec2 : public Vec2<int> {
public:
    using Vec2<int>::Vec2;

    iVec2(Vec2<int> v);

//    iVec2& operator=(const iVec2 &other) {
//        return Vec2<int>::operator=(other);
//    };
    iVec2& operator+=(const iVec2 &other) {
        Vec2<int>::operator+=(other);
        return *this;
    };
    iVec2& operator+=(int t) {
        Vec2<int>::operator+=(t);
        return *this;
    };
    iVec2 operator+(const iVec2 &other) const {
        return Vec2<int>::operator+(other);
    };
    iVec2 operator+(int t) const {
        return Vec2<int>::operator+(t);
    };
    iVec2& operator-=(const iVec2 &other) {
        Vec2<int>::operator-=(other);
        return *this;
    };
    iVec2& operator-=(int t) {
        Vec2<int>::operator-=(t);
        return *this;
    };
    iVec2 operator-(const iVec2 &other) const {
        return Vec2<int>::operator-(other);
    };
    iVec2 operator-(int t) const {
        return Vec2<int>::operator-(t);
    };
    iVec2& operator*=(const iVec2 &other) {
        Vec2<int>::operator*=(other);
        return *this;
    };
    iVec2& operator*=(int t) {
        Vec2<int>::operator*=(t);
        return *this;
    };
    iVec2 operator*(const iVec2 &other) const {
        return Vec2<int>::operator*(other);
    };
    iVec2 operator*(int t) const {
        return Vec2<int>::operator*(t);
    };
};

// float vector

class fVec2 : public Vec2<float> {
public:
    using Vec2<float>::Vec2;

    fVec2(Vec2<float> v);

    fVec2& operator+=(const fVec2 &other) {
        Vec2<float>::operator+=(other);
        return *this;
    };
    fVec2& operator+=(float t) {
        Vec2<float>::operator+=(t);
        return *this;
    };
    fVec2 operator+(const fVec2 &other) const {
        return Vec2<float>::operator+(other);
    };
    fVec2 operator+(float t) const {
        return Vec2<float>::operator+(t);
    };
    fVec2& operator-=(const fVec2 &other) {
        Vec2<float>::operator-=(other);
        return *this;
    };
    fVec2& operator-=(float t) {
        Vec2<float>::operator-=(t);
        return *this;
    };
    fVec2 operator-(const fVec2 &other) const {
        return Vec2<float>::operator-(other);
    };
    fVec2 operator-(float t) const {
        return Vec2<float>::operator-(t);
    };
    fVec2& operator*=(const fVec2 &other) {
        Vec2<float>::operator*=(other);
        return *this;
    };
    fVec2& operator*=(float t) {
        Vec2<float>::operator*=(t);
        return *this;
    };
    fVec2 operator*(const fVec2 &other) const {
        return Vec2<float>::operator*(other);
    };
    fVec2 operator*(float t) const {
        return Vec2<float>::operator*(t);
    };
};


#endif // VEC2_H