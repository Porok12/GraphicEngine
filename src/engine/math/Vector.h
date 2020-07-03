#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <cmath>
#include <vector>
#include <iostream>
//#include <boost/array.hpp>
//#include <array>

template <class type, int size>
class Vector {
protected:
    const int length = size;
    type array[size];
//    const boost::array<type, size> array{0};
//    const std::array<type, size> arr;
public:
    Vector();
    Vector(std::vector<type> v);

//    Vector(type... v) {
////        std::vector<type> vec = {v...};
////        for (int i = 0; i < vec.size(); ++i) {
////            array[i] = v[i];
////        }
//    }



//    template<typename... Args>
//    auto adder(Args... args) {
//        auto res = 0;
//        for(auto a: args) {
//            res += a;
//        }
//        return res;
//    }

    Vector& operator=(const Vector& other);
    Vector& operator+=(const Vector& other);
    Vector& operator+=(type t);
//    friend Vector& operator+(const Vector &left, const Vector &right) {
//        Vector<type, size> result;
//        for(int i = 0; i < size; i++) {
//            result.array[i] = left.array[i] + right.array[i];
//        }
//        return result;
//    }
    Vector operator-(const Vector& other) const;

    type& operator[](int i);
    Vector& normalize();
    type dot(const Vector &other);
};

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator=(const Vector &other) {
    if (this != &other) {
        for(int i = 0; i < size; i++) {
            this->array[i] += other.array[i];
        }
    }
    return *this;
}

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator+=(const Vector &other) {
    for(int i = 0; i < size; i++) {
        this->array[i] += other.array[i];
    }
    return *this;
}

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator+=(type t) {
    for(int i = 0; i < size; i++) {
        this->array[i] += t;
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
Vector<type, size>& Vector<type, size>::normalize() {
    double d = 0;
    auto square = [](type i) { return i*i; };
    for (auto e: this->array) {
        d += square(e);
    }

    d = sqrt(d);

    for(int i = 0; i < size; i++) {
        this->array[i] /= d;
    }

    return *this;
}

template<class type, int size>
type Vector<type, size>::dot(const Vector &other) {
    type result = 0;

    for (int i = 0; i < size; ++i) {
        result += this->array[i] * other.array[i];
    }

    return result;
}

template<class type, int size>
Vector<type, size> Vector<type, size>::operator-(const Vector &other) const {
//    for (int i = 0; i < size; ++i) {
//        std::cout << "Vector<type, size> " << this->array[i] << " " << other.array[i] << std::endl;
//    }
//    return Vector<type, size>();

    Vector<type, size> result;

    for (int i = 0; i < size; ++i) {
        result.array[i] = this->array[i] - other.array[i];
    }

    return result;
}

template<class type, int size>
Vector<type, size>::Vector(std::vector<type> v) {
    for (int i = 0; i < v.size(); ++i) {
        this->array[i] = v[i];
    }
}

template<class type, int size>
Vector<type, size>::Vector() {
    for (int i = 0; i < size; ++i) {
        this->array[i] = 0;
    }
};


//---------------------------------------

template <class type>
class Property {
private:
    type* ptr;
public:
    type& operator+=(const type &i) { return *ptr += i; }
    type& operator-=(const type &i) { return *ptr -= i; }
    type& operator= (const type &i) { return *ptr = i; }
    operator type() const { return *ptr; }

    Property(type* ptr) { this->ptr = ptr; }
//    Property() { }
};


#endif // VECTOR_H