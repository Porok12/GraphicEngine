#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <cmath>
#include <vector>

template <class type, int size>
class Vector {
protected:
    type array[size];
public:
    Vector();
    Vector(std::vector<type> v);

    type& operator[](int i);
    Vector& normalize();
    type dot(const Vector &other);
    Vector& operator=(const Vector& other);
    Vector& operator+=(const Vector& other);
    Vector& operator+=(type t);
    Vector operator+(const Vector& other) const;
    Vector operator+(type t) const;
    Vector& operator-=(const Vector& other);
    Vector& operator-=(type t);
    Vector operator-(const Vector& other) const;
    Vector operator-(type t) const;
    Vector& operator*=(const Vector& other);
    Vector& operator*=(type t);
    Vector operator*(const Vector& other) const;
    Vector operator*(type t) const;
};

// ------------------ Utils ---------------------

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
};


#endif // VECTOR_H