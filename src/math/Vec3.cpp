#include "engine/math/Vec3.h"

template<class type>
Vec3<type>::Vec3(Vector<type, 3> v)
        : Vector<type, 3>({v[0], v[1], v[2]}),
          x(Property<type>(&this->array[0])),
          y(Property<type>(&this->array[1])),
          z(Property<type>(&this->array[2])) {
    this->array[0] = v[0];
    this->array[1] = v[1];
    this->array[2] = v[2];
}

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

template class Vec3<int>;
template class Vec3<float>;

iVec3::iVec3(const iVec3 &v) {
    array[0] = v.array[0];
    array[1] = v.array[1];
    array[2] = v.array[2];
}

iVec3::iVec3(Vec3<int> v)
        : Vec3<int>(v.x, v.y, v.z) {

}

iVec3 iVec3::cross(const iVec3 &other) {
    return Vec3<int>::cross(other);
}


fVec3::fVec3(const fVec3 &v) {
    array[0] = v.array[0];
    array[1] = v.array[1];
    array[2] = v.array[2];
    this->x = this->array[0];
    this->y = this->array[1];
    this->z = this->array[2];
}

fVec3::fVec3(Vec3<float> v)
        : Vec3<float>(v.x, v.y, v.z) {
    this->x = this->array[0];
    this->y = this->array[1];
    this->z = this->array[2];
}

fVec3 fVec3::cross(const fVec3 &other) {
    return Vec3<float>::cross(other);
}