#ifndef VEC2_H
#define VEC2_H

template <class type>
class Vec2 {
private:
public:
    type x, y;
    Vec2(type x, type y);
    Vec2(type xy);
    Vec2();

    Vec2& operator=(const Vec2& other);
    Vec2& operator+(const Vec2& other);
    Vec2& operator-(const Vec2& other);
};

template <class type>
Vec2<type>::Vec2(type x, type y) {
    this->x = x;
    this->y = y;
}

template<class type>
Vec2<type>::Vec2(type xy) : Vec2(xy, xy) { }

template<class type>
Vec2<type>::Vec2() : Vec2(0) { }

template<class type>
Vec2<type> &Vec2<type>::operator=(const Vec2 &other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}

template<class type>
Vec2<type> &Vec2<type>::operator+(const Vec2 &other) {
    Vec2 result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    return result;
}

template<class type>
Vec2<type> &Vec2<type>::operator-(const Vec2 &other) {
    Vec2 result;
    result.x = this->x - other.x;
    result.y = this->y - other.y;
    return result;
}

#endif // VEC2_H