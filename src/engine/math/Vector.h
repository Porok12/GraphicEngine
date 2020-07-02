#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
//#include <boost/array.hpp>
//#include <array>

template <class type, int size>
class Vector {
protected:
    const int length = size;
    type array[size] {};
//    const boost::array<type, size> array{0};
//    const std::array<type, size> arr;
public:
    Vector();

    Vector& operator+=(const Vector &other);
    friend Vector& operator+(const Vector &left, const Vector &right) {
        Vector<type, size> result;
        for(int i = 0; i < size; i++) {
            result.array[i] = left.array[i] + right.array[i];
        }
        return result;
    }

    type& operator[](int i);
};

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator+=(const Vector &other) {
    for(int i = 0; i < size; i++) {
        this->array[i] += other.array[i];
    }
    return *this;
}

template<class type, int size>
type& Vector<type, size>::operator[](int i) {
    if (i >= 0 && i < size) {
        return this->array[i];
    } else {
        throw std::out_of_range("Parameter must be integer value between 0 and 2");
    }
}

template<class type, int size>
Vector<type, size>::Vector() = default;

template <class type>
class Property {
private:
    type* ptr;
public:
    type& operator= (const type &i) { return *ptr = i; }
    operator type() const { return *ptr; }

    Property(type* ptr) { this->ptr = ptr; }
};

template <class type>
class Vec2 : public Vector<type, 2> {
public:
//    class {
//    private:
//        type value;
//    public:
//        type& operator= (const type &i) { return value = i; }
//        operator type() const { return value; }
//    } x;
//
//    class {
//    private:
//        type value;
//    public:
//        type& operator= (const type &i) { return value = i; }
//        operator type() const { return value; }
//    } y;

//    Property<type> z;
    Property<type> x, y;

    Vec2(type x, type y);
    Vec2(type xy);
    Vec2();

//    friend Vec2& operator+(const Vec2 &left, const Vec2 &right) {
//        return static_cast<Vec2<int>&>(
//                static_cast<Vector<type, 2>>(left) +
//                static_cast<Vector<type, 2>>(right));
//    }

    Vec2& operator+=(const Vec2 &other) {
        Vector<type, 2>::operator+=(other);
        return *this;
    }
};

//template<class type>
//Vec2<type>::Vec2(type x, type y) : z(Property<type>(this->array)){
//    this->array[0] = x;
//    this->array[1] = y;
//
//    this->x = this->array[0];
//    this->y = this->array[1];
//}

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

class iVec2 : public Vec2<int> {
public:
    using Vec2<int>::Vec2;

//    friend iVec2& operator+(const iVec2 &left, const iVec2 &right) {
//        return static_cast<iVec2&>(
//                        static_cast<Vec2<int>>(left) +
//                        static_cast<Vec2<int>>(right));
//    }

    iVec2& operator+=(const iVec2 &other);
};

iVec2 &iVec2::operator+=(const iVec2 &other) {
    Vec2<int>::operator+=(other);
    return *this;
}


#endif // VECTOR_H