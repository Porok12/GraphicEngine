#include "engine/math/Mat4.h"

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

Mat4 Mat4::identity() {
    Mat4 mat;
    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;

    return mat;
}

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

    return mat;
}

Mat4 Mat4::translate(Mat4 &mat, const float &x, const float &y, const float &z) {
    mat[3][0] = x;
    mat[3][1] = y;
    mat[3][2] = z;

    return mat;
}

Mat4 Mat4::lookAt(const fVec3 &pos, const fVec3 &tar, const fVec3 &_up) {
    fVec3 up = _up;
    up.normalize();
    fVec3 forward = (pos - tar);
    forward.normalize();
    fVec3 right = up.cross(forward);
    up = forward.cross(right);
    up.normalize();

    Mat4 mat;
    mat[0][0] = right[0];        mat[0][1] = up[0];        mat[0][2] = forward[0];        mat[0][3] = 0;
    mat[1][0] = right[1];        mat[1][1] = up[1];        mat[1][2] = forward[1];        mat[1][3] = 0;
    mat[2][0] = right[2];        mat[2][1] = up[2];        mat[2][2] = forward[2];        mat[2][3] = 0;
    mat[3][0] = -right.dot(pos); mat[3][1] = -up.dot(pos); mat[3][2] = -forward.dot(pos); mat[3][3] = 1;

    return mat;
}

Mat4 Mat4::operator*(const Mat4 &other) {
    Mat4 mat;
    Mat4 m1 = *this;
    Mat4 m2 = other;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                mat[loc(i, j)] += m1[i][k] * m2[k][j];
            }
        }
    }

    for (int m = 0; m < 4; ++m) {
        for (int n = 0; n < 4; ++n) {
            mat[m][n] = round(mat[m][n] * 1000000.0 ) / 1000000.0;
        }
    }

    return mat;
}

Mat4& Mat4::operator*=(const Mat4 &other) {
    return *this = this->operator*(other);
}

Mat4 Mat4::getOrtho(const float &left, const float &right, const float &bottom, const float &top,
                    const float &near, const float &far) {
    Mat4 mat;
    float width = right - left;
    float height = top - bottom;

    mat[0][0] = 2 / width;
    mat[1][1] = 2 / height;
    mat[2][2] = -2 / (far - near);
    mat[3][3] = 1;
    mat[3][0] = - (right + left) / (right - left);
    mat[3][1] = - (top + bottom) / (top - bottom);
    mat[3][2] = - (far + near) / (far - near);

    return mat;
}

Mat4 Mat4::scale(Mat4 &mat, const float &s, const fVec3 &v) {
    mat[0][0] = v.x * s;
    mat[1][1] = v.y * s;
    mat[2][2] = v.z * s;

    return mat;
}

Mat4 Mat4::scale(const float &s, const fVec3 &v) {
    Mat4 mat;
    mat[0][0] = v.x * s;
    mat[1][1] = v.y * s;
    mat[2][2] = v.z * s;
    mat[3][3] = 1;
    return mat;
}

Mat4 Mat4::rotationX(const float &angle) {
    Mat4 mat;

    auto D2R = (float)(M_PI / 180.0);

    mat[0][0] = 1;
    mat[1][1] = std::cos(D2R*angle);
    mat[2][2] = std::cos(D2R*angle);
    mat[3][3] = 1;
    mat[1][2] = -std::sin(D2R*angle);
    mat[2][1] = std::sin(D2R*angle);

    return mat;
}

Mat4 Mat4::rotationY(const float &angle) {
    Mat4 mat;

    auto D2R = (float)(M_PI / 180.0);

    mat[0][0] = std::cos(D2R*angle);
    mat[1][1] = 1;
    mat[2][2] = std::cos(D2R*angle);
    mat[3][3] = 1;
    mat[0][2] = std::sin(D2R*angle);
    mat[2][0] = -std::sin(D2R*angle);

    return mat;
}

Mat4 Mat4::rotationZ(const float &angle) {
    Mat4 mat;

    auto D2R = (float)(M_PI / 180.0);

    mat[0][0] = std::cos(D2R*angle);
    mat[1][1] = std::cos(D2R*angle);
    mat[2][2] = 1;
    mat[3][3] = 1;
    mat[0][1] = std::sin(D2R*angle);
    mat[1][0] = -std::sin(D2R*angle);

    return mat;
}

Mat4 Mat4::rotation(const float &angle, fVec3 u) {
    Mat4 m;
    u.normalize();
    auto D2R = (float)(M_PI / 180.0);
    float a = angle * D2R;
    float c = std::cos(a);
    float s = std::sin(a);
    m[0][0] = c+u.x*u.x*(1-c); m[0][1] = u.x*u.y*(1-c)-u.z*s; m[0][2] = u.x*u.z*(1-c)+u.y*s;
    m[1][0] = u.y*u.x*(1-c)+u.z*s; m[1][1] = c+u.y*u.y*(1-c); m[1][2] = u.y*u.z*(1-c)-u.x*s;
    m[2][0] = u.z*u.x*(1-c)-u.y*s; m[2][1] = u.z*u.y*(1-c)+u.x*s; m[2][2] = c+u.z*u.z*(1-c);
    m[3][3] = 1;

    return m;
}

Mat4 &Mat4::inverse() {
//    throw NotImplementedException();
    double a11 = (*this)[0][0]; double a12 = (*this)[0][1]; double a13 = (*this)[0][2]; double a14 = (*this)[0][3];
    double a21 = (*this)[1][0]; double a22 = (*this)[1][1]; double a23 = (*this)[1][2]; double a24 = (*this)[1][3];
    double a31 = (*this)[2][0]; double a32 = (*this)[2][1]; double a33 = (*this)[2][2]; double a34 = (*this)[2][3];
    double a41 = (*this)[3][0]; double a42 = (*this)[3][1]; double a43 = (*this)[3][2]; double a44 = (*this)[3][3];

    double determinant = 0;

    determinant =
              a11*a22*a33*a44 + a11*a23*a34*a42 + a11*a24*a32*a43
            - a11*a24*a33*a42 - a11*a23*a32*a44 - a11*a22*a34*a43
            - a12*a21*a33*a44 - a13*a21*a34*a42 - a14*a21*a32*a43
            + a14*a21*a33*a42 + a13*a21*a32*a44 + a12*a21*a34*a43
            + a12*a23*a31*a44 + a13*a24*a31*a42 + a14*a22*a31*a43
            - a14*a23*a31*a42 - a13*a22*a31*a44 - a12*a24*a31*a43
            - a12*a23*a34*a41 - a13*a24*a32*a41 - a14*a22*a33*a41
            + a14*a23*a32*a41 + a13*a22*a34*a41 + a12*a24*a33*a41;

    //adjugate
    double adj11 =   a22*a33*a44 + a23*a34*a42 + a24*a32*a43
                  - a24*a33*a42 - a23*a32*a44 - a22*a34*a43;
    double adj12 = - a12*a33*a44 - a13*a34*a42 - a14*a32*a43
                  + a14*a33*a42 + a13*a32*a44 + a12*a34*a43;
    double adj13 =   a12*a23*a44 + a13*a24*a42 + a14*a22*a43
                  - a14*a23*a42 - a13*a22*a44 - a12*a24*a43;
    double adj14 = - a12*a23*a34 - a13*a24*a32 - a14*a22*a33
                  + a14*a23*a32 + a13*a22*a34 + a12*a24*a33;

    double adj21 = - a21*a33*a44 - a23*a34*a41 - a24*a31*a43
                  + a24*a33*a41 + a23*a31*a44 + a21*a34*a43;
    double adj22 =   a11*a33*a44 + a13*a34*a41 + a14*a31*a43
                  - a14*a33*a41 - a13*a31*a44 - a11*a34*a43;
    double adj23 = - a11*a23*a44 - a13*a24*a41 - a14*a21*a43
                  + a14*a23*a41 + a13*a21*a44 + a11*a24*a43;
    double adj24 =   a11*a23*a34 + a13*a24*a31 + a14*a21*a33
                  - a14*a23*a31 - a13*a21*a34 - a11*a24*a33;

    double adj31 =   a21*a32*a44 + a22*a34*a41 + a24*a31*a42
                  - a24*a32*a41 - a22*a31*a44 - a21*a34*a42;
    double adj32 = - a11*a32*a44 - a12*a34*a41 - a14*a31*a42
                  + a14*a32*a41 + a12*a31*a44 + a11*a34*a42;
    double adj33 =   a11*a22*a44 + a12*a21*a41 + a14*a21*a42
                  - a14*a22*a41 - a12*a24*a44 - a11*a24*a42;
    double adj34 = - a11*a22*a34 - a12*a24*a31 - a14*a21*a32
                  + a14*a22*a31 + a12*a21*a34 + a11*a24*a32;

    double adj41 = - a21*a32*a43 - a22*a33*a41 - a23*a31*a42
                  + a23*a32*a41 + a22*a31*a43 + a21*a33*a42;
    double adj42 =   a11*a32*a43 + a12*a33*a41 + a13*a31*a42
                  - a13*a32*a41 - a12*a31*a43 - a11*a33*a42;
    double adj43 = - a11*a22*a43 - a12*a23*a41 - a13*a21*a42
                  + a13*a22*a41 + a12*a21*a43 + a11*a23*a42;
    double adj44 =   a11*a22*a33 + a12*a23*a31 + a13*a21*a32
                  - a13*a22*a31 - a12*a21*a33 - a11*a23*a32;

    double d = determinant;
    (*this)[0][0] = adj11 / d; (*this)[0][1] = adj12 / d; (*this)[0][2] = adj13 / d; (*this)[0][3] = adj14 / d;
    (*this)[1][0] = adj21 / d; (*this)[1][1] = adj22 / d; (*this)[1][2] = adj23 / d; (*this)[1][3] = adj24 / d;
    (*this)[2][0] = adj31 / d; (*this)[2][1] = adj32 / d; (*this)[2][2] = adj33 / d; (*this)[2][3] = adj34 / d;
    (*this)[3][0] = adj41 / d; (*this)[3][1] = adj42 / d; (*this)[3][2] = adj43 / d; (*this)[3][3] = adj44 / d;

    return *this;

}

fVec4 Mat4::operator*(fVec4 &other) {
    fVec4 vec(0);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            vec[i] += (&other)->operator[](j) * (*this)[i][j];
        }
    }

    return vec;
}
