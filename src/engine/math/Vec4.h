#ifndef VEC4_H
#define VEC4_H

#include "Vector.h"

template <class type>
class Vec4 : public Vector<type, 4> {
public:
    Property<type> x, y, z, w;

    Vec4(type x, type y, type z, type w);
    Vec4(type xyzw);
    Vec4();

    Vec4& operator+=(const Vec4 &other) {
        Vector<type, 4>::operator+=(other);
        return *this;
    }
};

template<class type>
Vec4<type>::Vec4(type x, type y, type z, type w)
        : x(Property<type>(this->array+0)),
          y(Property<type>(this->array+1)),
          z(Property<type>(this->array+2)),
          w(Property<type>(this->array+3)){
    this->array[0] = x;
    this->array[1] = y;
    this->array[2] = z;
    this->array[3] = w;
}

template<class type>
Vec4<type>::Vec4(type xyzw) : Vec4(xyzw, xyzw, xyzw, xyzw) {

}

template<class type>
Vec4<type>::Vec4() : Vec4(0) {

}

// -------------------------------------------------

class iVec4 : public Vec4<int> {
public:
    using Vec4<int>::Vec4;

    iVec4& operator+=(const iVec4 &other);
};

iVec4 &iVec4::operator+=(const iVec4 &other) {
    Vec4<int>::operator+=(other);
    return *this;
}

class fVec4 : public Vec4<float> {
public:
    using Vec4<float>::Vec4;
};

#endif // VEC4_H