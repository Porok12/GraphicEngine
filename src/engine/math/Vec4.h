#ifndef VEC4_H
#define VEC4_H

#include "Vector.h"

template <class type>
class Vec4 : public Vector<type, 4> {
public:
    Property<type> x, y, z, w;

    Vec4(Vector<type, 4> v);
    Vec4(type x, type y, type z, type w);
    Vec4(type xyzw);
    Vec4();

    Vec4& operator+=(const Vec4 &other) {
        Vector<type, 4>::operator+=(other);
        return *this;
    }
    Vec4& operator+=(type t) {
        Vector<type, 4>::operator+=(t);
        return *this;
    }
    Vec4 operator+(const Vec4& other) const {
        return Vector<type, 4>::operator+(other);
    }
    Vec4 operator+(type t) const {
        return Vector<type, 4>::operator+(t);
    }
    Vec4& operator-=(const Vec4 &other) {
        Vector<type, 4>::operator-=(other);
        return *this;
    }
    Vec4& operator-=(type t) {
        Vector<type, 4>::operator-=(t);
        return *this;
    }
    Vec4 operator-(const Vec4& other) const {
        return Vector<type, 4>::operator-(other);
    }
    Vec4 operator-(type t) const {
        return Vector<type, 4>::operator-(t);
    }
    Vec4& operator*=(const Vec4 &other) {
        Vector<type, 4>::operator*=(other);
        return *this;
    }
    Vec4& operator*=(type t) {
        Vector<type, 4>::operator*=(t);
        return *this;
    }
    Vec4 operator*(const Vec4& other) const {
        return Vector<type, 4>::operator*(other);
    }
    Vec4 operator*(type t) const {
        return Vector<type, 4>::operator*(t);
    }
};

// -------------------------------------------------

// integer vector

class iVec4 : public Vec4<int> {
public:
    using Vec4<int>::Vec4;

    iVec4(const iVec4 &other);
    iVec4(Vec4<int> v);

    iVec4& operator+=(int t) {
        Vec4<int>::operator+=(t);
        return *this;
    }
    iVec4 operator+(const iVec4& other) const {
        return Vec4<int>::operator+(other);
    }
    iVec4 operator+(int t) const {
        return Vec4<int>::operator+(t);
    }
    iVec4& operator-=(const iVec4 &other) {
        Vec4<int>::operator-=(other);
        return *this;
    }
    iVec4& operator-=(int t) {
        Vec4<int>::operator-=(t);
        return *this;
    }
    iVec4 operator-(const iVec4& other) const {
        return Vec4<int>::operator-(other);
    }
    iVec4 operator-(int t) const {
        return Vec4<int>::operator-(t);
    }
    iVec4& operator*=(const iVec4 &other) {
        Vec4<int>::operator*=(other);
        return *this;
    }
    iVec4& operator*=(int t) {
        Vec4<int>::operator*=(t);
        return *this;
    }
    iVec4 operator*(const iVec4& other) const {
        return Vec4<int>::operator*(other);
    }
    iVec4 operator*(int t) const {
        return Vec4<int>::operator*(t);
    }
};

// float vector

class fVec4 : public Vec4<float> {
public:
    using Vec4<float>::Vec4;

    fVec4(const fVec4 &v);
    fVec4(Vec4<float> v);

    fVec4& operator+=(const fVec4 &other) {
        Vec4<float>::operator+=(other);
        return *this;
    }
    fVec4& operator+=(float t) {
        Vec4<float>::operator+=(t);
        return *this;
    }
    fVec4 operator+(const fVec4& other) const {
        return Vec4<float>::operator+(other);
    }
    fVec4 operator+(float t) const {
        return Vec4<float>::operator+(t);
    }
    fVec4& operator-=(const fVec4 &other) {
        Vec4<float>::operator-=(other);
        return *this;
    }
    fVec4& operator-=(float t) {
        Vec4<float>::operator-=(t);
        return *this;
    }
    fVec4 operator-(const fVec4& other) const {
        return Vec4<float>::operator-(other);
    }
    fVec4 operator-(float t) const {
        return Vec4<float>::operator-(t);
    }
    fVec4& operator*=(const fVec4 &other) {
        Vec4<float>::operator*=(other);
        return *this;
    }
    fVec4& operator*=(float t) {
        Vec4<float>::operator*=(t);
        return *this;
    }
    fVec4 operator*(const fVec4& other) const {
        return Vec4<float>::operator*(other);
    }
    fVec4 operator*(float t) const {
        return Vec4<float>::operator*(t);
    }
};

#endif // VEC4_H