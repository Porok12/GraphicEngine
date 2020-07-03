#ifndef VEC2_H
#define VEC2_H

#include "Vector.h"

template <class type>
class Vec2 : public Vector<type, 2> {
public:
    Property<type> x, y;

    Vec2(Vector<type, 2> v);
    Vec2(type x, type y);
    Vec2(type xy);
    Vec2();

    Vec2& operator+=(const Vec2 &other) {
        Vector<type, 2>::operator+=(other);
        return *this;
    }
    Vec2 operator-(const Vec2 &other) const;
};

//template<class type>
//Vec2<type>::Vec2(Vector<type, 2> v)
//        : Vector<type, 2>(v[0], v[1]) { //}, x(Property<type>(&v.array[0]+0)), y(Property<type>(&v.array[0]+1)) {
//
//}

template<class type>
Vec2<type>::Vec2(Vector<type, 2> v)
        : Vector<type, 2>({v[0], v[1]}),
          x(Property<type>(&v[0]+0)),
          y(Property<type>(&v[0]+1)) {
}

template<class type>
Vec2<type>::Vec2(type x, type y)
        : x(Property<type>(this->array+0)),
          y(Property<type>(this->array+1)){
    this->array[0] = x;
    this->array[1] = y;
}

template<class type>
Vec2<type>::Vec2(type xy) : Vec2(xy, xy) {

}

template<class type>
Vec2<type>::Vec2() : Vec2(0) {

}

template<class type>
Vec2<type> Vec2<type>::operator-(const Vec2 &other) const {
//    return Vec2<type>();
    return Vector<type, 2>::operator-(other);
}

// -----------------------------

class iVec2 : public Vec2<int> {
public:
    using Vec2<int>::Vec2;

    iVec2(Vec2<int> v);
    iVec2& operator+=(const iVec2 &other);
    iVec2 operator-(const iVec2 &other) const;
};

iVec2::iVec2(Vec2<int> v)
        : Vec2<int>(v.x, v.y) {

}

iVec2 &iVec2::operator+=(const iVec2 &other) {
    Vec2<int>::operator+=(other);
    return *this;
}

iVec2 iVec2::operator-(const iVec2 &other) const {
    return Vec2<int>::operator-(other);
}

class fVec2 : public Vec2<float> {
public:
    using Vec2<float>::Vec2;
};

#endif // VEC2_H