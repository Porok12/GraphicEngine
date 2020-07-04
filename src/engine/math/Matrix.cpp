#include "Matrix.h"

template<class type, int m, int n>
Matrix<type, m, n>::Matrix() {
};

template<class type, int m, int n>
type* Matrix<type, m, n>::operator[](int i) {
    if (i >= 0 && i < m) {
        return (&this->array[0]) + i * n;
    } else {
        throw std::out_of_range("Blablah");
    }
}

template<class type, int m, int n>
type& Matrix<type, m, n>::operator[](loc const& l) {
    if (l.x < 0 || l.x >= m) {
        throw std::out_of_range("x");
    }

    if (l.y < 0 || l.y >= n) {
        throw std::out_of_range("y");
    }

    return this->array[n * l.x + l.y];
}

template<class type, int m, int n>
Matrix<type, m, n> &Matrix<type, m, n>::operator+=(const Matrix &other) {
    for(int i = 0; i < m*n; i++) {
        this->array[i] += other.array[i];
    }
    return *this;
}

template<class type, int m, int n>
Matrix<type, m, n>& Matrix<type, m, n>::operator+=(type t) {
    for(int i = 0; i < m*n; i++) {
        this->array[i] += t;
    }
    return *this;
}

template class Matrix<float, 4, 4>;