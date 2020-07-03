#ifndef MAT4_H
#define MAT4_H

#include <cmath>
#include "Vec3.h"
#include "Matrix.h"

//template <class type>
class Mat4 : public Matrix<float, 4, 4> {
public:
    static Mat4 getProjection(const float &fov, const float &aspect, const float &near, const float &far);
    static Mat4 translate(const float &x, const float &y, const float &z);
    static Mat4 lookAt(const fVec3 &pos, const fVec3 &tar);
//
//    const type* getPtr();
};

//template<class type>
//const type* Mat4<type>::getPtr() {
//    return &this->array[0];
//}

//template<class type>
Mat4 Mat4::getProjection(const float &fov, const float &aspect, const float &near, const float &far) {
    Mat4 mat;
    float D2R = M_PI / 180.0;
    float yScale = 1.0 / tan(D2R * fov / 2);
    float xScale = yScale / aspect;
    float nearmfar = near - far;

    mat[loc(0, 0)] = xScale;
    mat[loc(1, 1)] = yScale;
    mat[loc(2, 2)] = (far + near) / nearmfar;
    mat[loc(3, 2)] = 2*far*near / nearmfar;
    mat[loc(2, 3)] = -1;

    return mat;
}

//template<class type>
Mat4 Mat4::translate(const float &x, const float &y, const float &z) {
    Mat4 mat;

    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
    mat[3][0] = x;
    mat[3][1] = y;
    mat[3][2] = z;

    return mat;
}

//template<class type>
Mat4 Mat4::lookAt(const fVec3 &pos, const fVec3 &tar) {
    fVec3 up(0, 1, 0);
    fVec3 forward = (pos - tar).normalize();
    fVec3 right = up.cross(forward).normalize();
    up = forward.cross(right);

    Mat4 mat;
    mat[0][0] = right[0]; mat[0][1] = right[1]; mat[0][2] = right[2]; mat[0][3] = right.dot(pos);
    mat[1][0] = up[0]; mat[1][1] = up[1]; mat[1][2] = up[2]; mat[1][3] = up.dot(pos);
    mat[2][0] = forward[0]; mat[2][1] = forward[1]; mat[2][2] = forward[2]; mat[2][3] = forward.dot(pos);
    mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;

    return mat;
}



#endif // MAT4_H