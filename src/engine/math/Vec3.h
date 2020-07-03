#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include "Vector.h"

template <class type>
class Vec3 : public Vector<type, 3> {
public:
    Property<type> x, y, z;

    Vec3(Vector<type, 3> v);
    Vec3(type x, type y, type z);
    Vec3(type xyz);
    Vec3();

    Vec3& operator+=(const Vec3 &other) {
        Vector<type, 3>::operator+=(other);
        return *this;
    }

    Vec3 cross(const Vec3& other);
    Vec3 operator-(const Vec3& other) const;
};

template<class type>
Vec3<type>::Vec3(Vector<type, 3> v)
        : Vector<type, 3>({v[0], v[1], v[2]}),
          x(Property<type>(&v[0])),
          y(Property<type>(&v[1])),
          z(Property<type>(&v[2])) {

}

//template<class type>
//Vec2<type>::Vec2(Vector<type, 2> v)
//        : Vector<type, 2>(v[0], v[1]) { //}, x(Property<type>(&v.array[0]+0)), y(Property<type>(&v.array[0]+1)) {
//
//}

//template<class type>
//Vec3<type>::Vec3(Vector<type, 3> v)
//        : x(Property<type>(&v[0])),
//          y(Property<type>(&v[1])),
//          z(Property<type>(&v[2])){
//    this->array[0] = v[0];
//    this->array[1] = v[1];
//    this->array[2] = v[2];
//}

template<class type>
Vec3<type>::Vec3(type x, type y, type z)
        : x(Property<type>(this->array+0)),
          y(Property<type>(this->array+1)),
          z(Property<type>(this->array+2)){
    this->array[0] = x;
    this->array[1] = y;
    this->array[2] = z;
}

template<class type>
Vec3<type>::Vec3(type xyz) : Vec3(xyz, xyz, xyz) {

}

template<class type>
Vec3<type>::Vec3() : Vec3(0) {

}

template<class type>
Vec3<type> Vec3<type>::cross(const Vec3 &other) {
    const type* a = &this->array[0];
    const type* b = &other.array[0];
    return Vec3<type>(
            a[1]*b[2] - a[2]*b[1],
            a[2]*b[0] - a[0]*b[2],
            a[0]*b[1] - a[1]*b[0]
    );
}

template<class type>
Vec3<type> Vec3<type>::operator-(const Vec3 &other) const {
    return Vector<type, 3>::operator-(other);
}

// -------------------------------------------------

class iVec3 : public Vec3<int> {
public:
    using Vec3<int>::Vec3;

    iVec3(Vec3<int> v);
    iVec3& operator+=(const iVec3 &other);
    iVec3 cross(const iVec3 &other);
};

iVec3::iVec3(Vec3<int> v)
        : Vec3<int>(v.x, v.y, v.z) {

}

iVec3 &iVec3::operator+=(const iVec3 &other) {
    Vec3<int>::operator+=(other);
    return *this;
}

iVec3 iVec3::cross(const iVec3 &other) {
    return Vec3<int>::cross(other);
}

class fVec3 : public Vec3<float> {
public:
    using Vec3<float>::Vec3;

    fVec3(Vec3<float> v);
    fVec3 cross(const fVec3 &other);
    fVec3 operator-(const fVec3& other) const;
};

fVec3::fVec3(Vec3<float> v)
        : Vec3<float>(v.x, v.y, v.z) { }

fVec3 fVec3::cross(const fVec3 &other) {
//    Vec3<float> c = Vec3<float>::cross(other);
//    return fVec3(c);
    return Vec3<float>::cross(other);
}

fVec3 fVec3::operator-(const fVec3 &other) const {
    return Vec3<float>::operator-(other);
}

#endif // VEC3_H