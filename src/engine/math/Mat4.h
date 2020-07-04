#ifndef MAT4_H
#define MAT4_H

#include <cmath>
#include <iomanip>
#include "Vec3.h"
#include "Matrix.h"

class Mat4 : public Matrix<float, 4, 4> {
public:
    Mat4(Matrix<float, 4, 4> m);
    Mat4();

    static Mat4 getProjection(const float &fov, const float &aspect, const float &near, const float &far);
    static Mat4 translate(const float &x, const float &y, const float &z);
    static Mat4 lookAt(const fVec3 &pos, const fVec3 &tar);

    Mat4 operator*(const Mat4 &other);

    const float* ptr();
};

#endif // MAT4_H