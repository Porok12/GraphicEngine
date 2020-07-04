#ifndef VEC3_H
#define VEC3_H

#include "Vector.h"

template <class type>
class Vec3 : public Vector<type, 3> {
public:
    Property<type> x, y, z;

//    Vec3(const Vec3 &v);
    Vec3(Vector<type, 3> v);
    Vec3(type x, type y, type z);
    Vec3(type xyz);
    Vec3();

    Vec3 cross(const Vec3& other);
    Vec3& operator+=(const Vec3 &other) {
        Vector<type, 3>::operator+=(other);
        return *this;
    }
    Vec3& operator+=(type t) {
        Vector<type, 3>::operator+=(t);
        return *this;
    }
    Vec3 operator+(const Vec3& other) const {
        return Vector<type, 3>::operator+(other);
    }
    Vec3 operator+(type t) const {
        return Vector<type, 3>::operator+(t);
    }
    Vec3& operator-=(const Vec3 &other) {
        Vector<type, 3>::operator-=(other);
        return *this;
    }
    Vec3& operator-=(type t) {
        Vector<type, 3>::operator-=(t);
        return *this;
    }
    Vec3 operator-(const Vec3& other) const {
        return Vector<type, 3>::operator-(other);
    }
    Vec3 operator-(type t) const {
        return Vector<type, 3>::operator-(t);
    }
    Vec3& operator*=(const Vec3 &other) {
        Vector<type, 3>::operator*=(other);
        return *this;
    }
    Vec3& operator*=(type t) {
        Vector<type, 3>::operator*=(t);
        return *this;
    }
    Vec3 operator*(const Vec3& other) const {
        return Vector<type, 3>::operator*(other);
    }
    Vec3 operator*(type t) const {
        return Vector<type, 3>::operator*(t);
    }
};

// -------------------------------------------------

// integer vector

class iVec3 : public Vec3<int> {
public:
    using Vec3<int>::Vec3;

    iVec3(Vec3<int> v);
    iVec3 cross(const iVec3 &other);
    iVec3& operator+=(const iVec3 &other) {
        Vec3<int>::operator+=(other);
        return *this;
    }
    iVec3& operator+=(int t) {
        Vec3<int>::operator+=(t);
        return *this;
    }
    iVec3 operator+(const iVec3& other) const {
        return Vec3<int>::operator+(other);
    }
    iVec3 operator+(int t) const {
        return Vec3<int>::operator+(t);
    }
    iVec3& operator-=(const iVec3 &other) {
        Vec3<int>::operator-=(other);
        return *this;
    }
    iVec3& operator-=(int t) {
        Vec3<int>::operator-=(t);
        return *this;
    }
    iVec3 operator-(const iVec3& other) const {
        return Vec3<int>::operator-(other);
    }
    iVec3 operator-(int t) const {
        return Vec3<int>::operator-(t);
    }
    iVec3& operator*=(const iVec3 &other) {
        Vec3<int>::operator*=(other);
        return *this;
    }
    iVec3& operator*=(int t) {
        Vec3<int>::operator*=(t);
        return *this;
    }
    iVec3 operator*(const iVec3& other) const {
        return Vec3<int>::operator*(other);
    }
    iVec3 operator*(int t) const {
        return Vec3<int>::operator*(t);
    }
};

// float vector

class fVec3 : public Vec3<float> {
public:
    using Vec3<float>::Vec3;

    fVec3(const fVec3 &v);
    fVec3(Vec3<float> v);
    fVec3 cross(const fVec3 &other);
    fVec3& operator+=(const fVec3 &other) {
        Vec3<float>::operator+=(other);
        return *this;
    }
    fVec3& operator+=(float t) {
        Vec3<float>::operator+=(t);
        return *this;
    }
    fVec3 operator+(const fVec3& other) const {
        return Vec3<float>::operator+(other);
    }
    fVec3 operator+(float t) const {
        return Vec3<float>::operator+(t);
    }
    fVec3& operator-=(const fVec3 &other) {
        Vec3<float>::operator-=(other);
        return *this;
    }
    fVec3& operator-=(float t) {
        Vec3<float>::operator-=(t);
        return *this;
    }
    fVec3 operator-(const fVec3& other) const {
        return Vec3<float>::operator-(other);
    }
    fVec3 operator-(float t) const {
        return Vec3<float>::operator-(t);
    }
    fVec3& operator*=(const fVec3 &other) {
        Vec3<float>::operator*=(other);
        return *this;
    }
    fVec3& operator*=(float t) {
        Vec3<float>::operator*=(t);
        return *this;
    }
    fVec3 operator*(const fVec3& other) const {
        return Vec3<float>::operator*(other);
    }
    fVec3 operator*(float t) const {
        return Vec3<float>::operator*(t);
    }
};

#endif // VEC3_H