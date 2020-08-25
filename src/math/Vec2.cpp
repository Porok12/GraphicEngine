#include "engine/math/Vec2.h"

template<class type>
Vec2<type>::Vec2(Vector<type, 2> v)
        : Vector<type, 2>({v[0], v[1]}),
          x(Property<type>(&v[0])),
          y(Property<type>(&v[1])){
    this->array[0] = v[0];
    this->array[1] = v[1];
}

template<class type>
Vec2<type>::Vec2(type x, type y)
        : x(Property<type>(this->array+0)),
          y(Property<type>(this->array+1)){
    this->array[0] = x;
    this->array[1] = y;
}

template<class type>
Vec2<type>::Vec2(type xy) : Vec2(xy, xy) { }

template<class type>
Vec2<type>::Vec2() : Vec2(0) { }

template class Vec2<int>;
template class Vec2<float>;

iVec2::iVec2(const iVec2 &other) {
    this->array[0] = other.array[0];
    this->array[1] = other.array[1];
}

iVec2::iVec2(Vec2<int> v)
        : Vec2<int>(v.x, v.y) { }



fVec2::fVec2(Vec2<float> v)
        : Vec2<float>(v.x, v.y) { }

fVec2::fVec2(const fVec2 &other) {
    this->array[0] = other.array[0];
    this->array[1] = other.array[1];
}