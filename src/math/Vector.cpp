#include "engine/math/Vector.h"

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

    if (d != 0) {
        for(int i = 0; i < size; i++) {
            this->array[i] /= d;
        }
    }

    return *this;
}

template<class type, int size>
type Vector<type, size>::dot(const Vector &other) const {
    type result = 0;

    for (int i = 0; i < size; ++i) {
        result += this->array[i] * other.array[i];
    }

    return result;
}

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator=(const Vector &other) {
    Vector<type, size> tmp(other);
    std::swap(array, tmp.array);
    return *this;
//    if (this == &other) {
//        return *this;
//    } else {
//        for (int i = 0; i < size; ++i) {
//            this->array[i] = other.array[i];
//        }
//        return *this;
//    }
//    if (this != &other) {
//        for(int i = 0; i < size; i++) {
//            this->array[i] = other.array[i];
//        }
//    }
//    return *this;
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
Vector<type, size> Vector<type, size>::operator+(const Vector &other) const {
    Vector<type, size> result;
    for (int i = 0; i < size; ++i) {
        result.array[i] = this->array[i] + other.array[i];
    }
    return result;
};

template<class type, int size>
Vector<type, size> Vector<type, size>::operator+(type t) const {
    Vector<type, size> result;
    for (int i = 0; i < size; ++i) {
        result.array[i] = this->array[i] + t;
    }
    return result;
};

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator-=(const Vector &other) {
    for(int i = 0; i < size; i++) {
        this->array[i] -= other.array[i];
    }
    return *this;
}

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator-=(type t) {
    for(int i = 0; i < size; i++) {
        this->array[i] -= t;
    }
    return *this;
}

template<class type, int size>
Vector<type, size> Vector<type, size>::operator-(const Vector &other) const {
    Vector<type, size> result;
    for (int i = 0; i < size; ++i) {
        result.array[i] = this->array[i] - other.array[i];
    }
    return result;
}

template<class type, int size>
Vector<type, size> Vector<type, size>::operator-(type t) const {
    Vector<type, size> result;
    for (int i = 0; i < size; ++i) {
        result.array[i] = this->array[i] - t;
    }
    return result;
}

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator*=(const Vector &other) {
    for(int i = 0; i < size; i++) {
        this->array[i] *= other.array[i];
    }
    return *this;
}

template<class type, int size>
Vector<type, size>& Vector<type, size>::operator*=(type t) {
    for(int i = 0; i < size; i++) {
        this->array[i] *= t;
    }
    return *this;
}

template<class type, int size>
Vector<type, size> Vector<type, size>::operator*(const Vector &other) const {
    Vector<type, size> result;
    for (int i = 0; i < size; ++i) {
        result.array[i] = this->array[i] * other.array[i];
    }
    return result;
}

template<class type, int size>
Vector<type, size> Vector<type, size>::operator*(type t) const {
    Vector<type, size> result;
    for (int i = 0; i < size; ++i) {
        result.array[i] = this->array[i] * t;
    }
    return result;
}

template class Vector<int, 2>;
template class Vector<int, 3>;
template class Vector<int, 4>;
template class Vector<float, 2>;
template class Vector<float, 3>;
template class Vector<float, 4>;
