#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <cmath>

struct loc {
    int x, y;
    loc(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

template <class type, int m, int n>
class Matrix {
protected:
    type array[m*n] {};
public:
    Matrix();
    Matrix& operator+=(const Matrix &other);
    Matrix& operator+=(type t);

    type* operator[](int i);
    type& operator[](loc const& l);
};

#endif // MATRIX_H