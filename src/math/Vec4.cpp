#include "engine/math/Vec4.h"

template<class type>
Vec4<type>::Vec4(Vector<type, 4> v)
        : Vector<type, 4>({v[0], v[1], v[2], v[3]}),
          x(Property<type>(&this->array[0])),
          y(Property<type>(&this->array[1])),
          z(Property<type>(&this->array[2])),
          w(Property<type>(&this->array[3])) {
    this->array[0] = v[0];
    this->array[1] = v[1];
    this->array[2] = v[2];
    this->array[3] = v[3];
}

template<class type>
Vec4<type>::Vec4(type x, type y, type z, type w)
        : x(Property<type>(this->array+0)),
          y(Property<type>(this->array+1)),
          z(Property<type>(this->array+2)),
          w(Property<type>(this->array+3)) {
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

template class Vec4<int>;
template class Vec4<float>;

iVec4::iVec4(const iVec4 &v) {
    array[0] = v.array[0];
    array[1] = v.array[1];
    array[2] = v.array[2];
    array[3] = v.array[3];
}

iVec4::iVec4(Vec4<int> v)
        : Vec4<int>(v.x, v.y, v.z, v.w) {

}


fVec4::fVec4(const fVec4 &v) {
    array[0] = v.array[0];
    array[1] = v.array[1];
    array[2] = v.array[2];
    array[3] = v.array[3];
    this->x = this->array[0];
    this->y = this->array[1];
    this->z = this->array[2];
    this->w = this->array[3];
}

fVec4::fVec4(Vec4<float> v)
        : Vec4<float>(v.x, v.y, v.z, v.w) {
    this->x = this->array[0];
    this->y = this->array[1];
    this->z = this->array[2];
    this->z = this->array[3];
}