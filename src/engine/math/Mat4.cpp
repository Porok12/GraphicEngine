#include "Mat4.h"

const float* Mat4::ptr() {
    return &this->array[0];
}

Mat4::Mat4(Matrix<float, 4, 4> mat)
        : Matrix<float, 4, 4>() {
    for (int m = 0; m < 4; ++m) {
        for (int n = 0; n < 4; ++n) {
            (*this)[m][n] = mat[m][n];
        }
    }
}

Mat4::Mat4() { }

Mat4 Mat4::getProjection(const float &fov, const float &aspect, const float &near, const float &far) {
    Mat4 mat;
    auto D2R = (float)(M_PI / 180.0);
    auto yScale = (float)(1.0 / tan(D2R * fov / 2));
    float xScale = yScale / aspect;
    float nearmfar = near - far;

    mat[loc(0, 0)] = xScale;
    mat[loc(1, 1)] = yScale;
    mat[loc(2, 2)] = (far + near) / nearmfar;
    mat[loc(3, 2)] = 2*far*near / nearmfar;
    mat[loc(2, 3)] = -1;
//    mat[loc(2, 3)] = 2*far*near / nearmfar;
//    mat[loc(3, 2)] = -1;

    return mat;
}

Mat4 Mat4::translate(const float &x, const float &y, const float &z) {
    Mat4 mat;

    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
    mat[3][0] = x;
    mat[3][1] = y;
    mat[3][2] = z;
//    mat[0][3] = x;
//    mat[1][3] = y;
//    mat[2][3] = z;

    return mat;
}

Mat4 Mat4::lookAt(const fVec3 &pos, const fVec3 &tar) {
    fVec3 up(0, 1, 0);
    fVec3 forward = (pos - tar);
    forward.normalize();
    fVec3 right = up.cross(forward);
    up = forward.cross(right);;
    up.normalize();

    Mat4 mat;
    mat[0][0] = right[0];   mat[0][1] = right[1];   mat[0][2] = right[2];   mat[0][3] = -right.dot(pos);
    mat[1][0] = up[0];      mat[1][1] = up[1];      mat[1][2] = up[2];      mat[1][3] = -up.dot(pos);
    mat[2][0] = forward[0]; mat[2][1] = forward[1]; mat[2][2] = forward[2]; mat[2][3] = -forward.dot(pos);
    mat[3][0] = 0;          mat[3][1] = 0;          mat[3][2] = 0;          mat[3][3] = 1;

    return mat;
}

Mat4 Mat4::operator*(const Mat4 &other) {
    Mat4 mat;
    Mat4 m1 = *this;
    Mat4 m2 = other;

    for (int m = 0; m < 4; ++m) {
        std::cerr << std::endl;
        for (int n = 0; n < 4; ++n) {
            mat[loc(m, n)] = m1[m][n] * m2[n][m];
        }
    }

    return mat;
}