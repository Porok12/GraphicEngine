#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <cmath>

template <class type, int n>
class X {
private:
    type* ptr = nullptr;
public:
//    type& operator= (const type &i) { return *ptr = i; }
//    operator type() const { return *ptr; }

//    X(type* ptr) : {
//        this->ptr = ptr;
//    }

    type& operator[](int i);
};

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
    const int length = m*n;
    type array[m*n] {};
    X<type, n> x[m] {};
public:
    Matrix();
    Matrix& operator+=(const Matrix &other);
    Matrix& operator+=(type t);

    type* operator[](int i);
    type& operator[](loc const& l);
};

template<class type, int m, int n>
Matrix<type, m, n>::Matrix() {
//    x = X<type, n>[m];
//    x[0] = &array[0];
//    x[1] = &array[0];
//    x[2] = &array[0];
//    x[3] = &array[0];
};

template <class type, int n>
type& X<type, n>::operator[](int i) {
    if (i >= 0 && i < n)
    return this->ptr[i];
}

template<class type, int m, int n>
type* Matrix<type, m, n>::operator[](int i) {
    if (i >= 0 && i < m) {
        return (&this->array[0]) + i * m;
    } else {
        throw std::out_of_range("Blablah");
    }
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

template<class type, int m, int n>
type& Matrix<type, m, n>::operator[](loc const& l) {
    return this->array[m * l.x + n * l.y];
}


//---------------------------------------

template <class type>
class Help {
private:
    type* ptr;
public:
    type& operator= (const type &i) { return *ptr = i; }
    operator type() const { return *ptr; }

    Help(type* ptr) { this->ptr = ptr; }
};

template <class type>
class Row {
private:
    type* ptr;
public:
    type& operator= (const type &i) { return *ptr = i; }
    operator type() const { return *ptr; }

    Row(type* ptr) { this->ptr = ptr; }
};

template <class type>
class Column {
private:
    type* ptr;
public:
    type& operator= (const type &i) { return *ptr = i; }
    operator type() const { return *ptr; }

    Column(type* ptr) { this->ptr = ptr; }
};


#endif // MATRIX_H