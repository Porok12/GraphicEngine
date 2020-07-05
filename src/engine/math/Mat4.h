#ifndef MAT4_H
#define MAT4_H

#include <iostream>
#include <cmath>
#include "Vec3.h"
#include "Matrix.h"

class Mat4 : public Matrix<float, 4, 4> {
public:
    Mat4(Matrix<float, 4, 4> m);
    Mat4();

    static Mat4 identity();
    static Mat4 getOrtho(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far);
    static Mat4 getProjection(const float &fov, const float &aspect, const float &near, const float &far);
    static Mat4 lookAt(const fVec3 &pos, const fVec3 &tar);
    static Mat4 translate(const float &x, const float &y, const float &z);
    static Mat4 translate(Mat4 &mat, const float &x, const float &y, const float &z);
    static Mat4 scale(Mat4 &mat, const float &s, const fVec3 &v = fVec3(1.0f, 1.0f, 1.0f));
    static Mat4 scale(const float &s, const fVec3 &v = fVec3(1.0f, 1.0f, 1.0f));

    static Mat4 rotationX(const float &angle);
    static Mat4 rotationY(const float &angle);
    static Mat4 rotationZ(const float &angle);
    static Mat4 rotation(const float &angle, fVec3 u = fVec3(1.0f));

    Mat4 operator*(const Mat4 &other);
    Mat4& operator*=(const Mat4 &other);

    const float* ptr();

    friend std::ostream &operator<<(std::ostream &output, const Mat4& mat) {
        for (int m = 0; m < 4; ++m) {
            output << std::endl;
            for (int n = 0; n < 4; ++n) {
                output << mat.array[m*4+n]  << " ";
            }
        }
        output << std::endl;
    }
};


#endif // MAT4_H