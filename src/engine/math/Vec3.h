#ifndef VEC3_H
#define VEC3_H

#include <math.h>

template <class type>
class Vec3 {
private:
public:
    type x, y, z;
    Vec3(type x, type y, type z);
    Vec3(type xyz);
    Vec3();

    Vec3& operator=(const Vec3& other);
    Vec3& operator+(const Vec3& other);
    Vec3& operator-(const Vec3& other);
    Vec3& normalize();
    static const Vec3<type>& normalize(const Vec3& other);
};

template <class type>
Vec3<type>::Vec3(type x, type y, type z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template<class type>
Vec3<type>::Vec3(type xyz) : Vec3(xyz, xyz, xyz) { }

template<class type>
Vec3<type>::Vec3() : Vec3(0) { }

template<class type>
Vec3<type> &Vec3<type>::operator=(const Vec3 &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

template<class type>
Vec3<type> &Vec3<type>::operator+(const Vec3 &other) {
    Vec3 result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    result.z = this->z + other.z;
    return result;
}

template<class type>
Vec3<type> &Vec3<type>::operator-(const Vec3 &other) {
    Vec3 result;
    result.x = this->x - other.x;
    result.y = this->y - other.y;
    result.z = this->z - other.z;
    return result;
}

template<class type>
Vec3<type> &Vec3<type>::normalize() {
    type d = sqrt(x*x + y*y + z*z);
    x /= d;
    y /= d;
    z /= d;
    return *this;
}

template<class type>
const Vec3<type>& Vec3<type>::normalize(const Vec3 &other) {
    other.x /= 1;
    return other;
}


#endif // VEC3_H