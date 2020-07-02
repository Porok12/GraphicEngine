#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <stdexcept>

template <class type>
class Vec3 {
private:
    unsigned int lenght;
public:
    type x, y, z;
    Vec3(type x, type y, type z);
    Vec3(type xyz);
    Vec3();

    type operator[](int i);
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

template<class type>
type Vec3<type>::operator[](int i) {
    switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 3:
            return z;
        default:
            throw std::out_of_range("Parameter must be integer value between 0 and 2");
    }
}


#endif // VEC3_H