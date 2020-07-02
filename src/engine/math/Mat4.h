#ifndef MAT4_H
#define MAT4_H

#include <cmath>
#include "Vec3.h"

template <class type>
class Mat4 {
private:
    type M[4*4];
public:
    static Mat4 getProjection(const float &fov, const float &aspect, const float &near, const float &far);
    static Mat4 translate(const float &x, const float &y, const float &z);
    static Mat4 lookAt(const Vec3<type> &pos, const Vec3<type> &tar);

    const type* getPtr();
};

template<class type>
Mat4<type> Mat4<type>::getProjection(const float &fov, const float &aspect, const float &near, const float &far) {
//    Mat4<type> mat4;
//    auto scale = static_cast<float>(1 / tan(angle * 0.5 * M_PI / 180));
//
//    mat4.M[0][0] = scale; // scale the x coordinates of the projected point
//    mat4.M[1][1] = scale; // scale the y coordinates of the projected point
//    mat4.M[2][2] = -far / (far - near); // used to remap z to [0,1]
//    mat4.M[3][2] = -far * near / (far - near); // used to remap z [0,1]
//    mat4.M[2][3] = -1; // set w = -z
//    mat4.M[3][3] = 0;
//    return mat4;

    Mat4<type> mat4;
    type D2R = M_PI / 180.0;
    type yScale = 1.0 / tan(D2R * fov / 2);
    type xScale = yScale / aspect;
    type nearmfar = near - far;
    //    mat4.M[0][0] = scale; // scale the x coordinates of the projected point
//    mat4.M[1][1] = scale; // scale the y coordinates of the projected point
//    mat4.M[2][2] = -far / (far - near); // used to remap z to [0,1]
//    mat4.M[3][2] = -far * near / (far - near); // used to remap z [0,1]
//    mat4.M[2][3] = -1; // set w = -z
//    mat4.M[3][3] = 0;

    type m[] = {
            xScale, 0, 0, 0,
            0, yScale, 0, 0,
            0, 0, (far + near) / nearmfar, -1,
            0, 0, 2*far*near / nearmfar, 0
    };

    for (int i = 0; i < 4 * 4; ++i) {
        mat4.M[i] = m[i];
    }

    return mat4;
}

template<class type>
const type* Mat4<type>::getPtr() {
    return &M[0];
}

template<class type>
Mat4<type> Mat4<type>::translate(const float &x, const float &y, const float &z) {
    Mat4<type> mat4;
    type m[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1
    };

    for (int i = 0; i < 4 * 4; ++i) {
        mat4.M[i] = m[i];
    }
    return mat4;
}

template<class type>
Mat4<type> Mat4<type>::lookAt(const Vec3<type> &pos, const Vec3<type> &tar) {
    return Mat4();
}

#endif // MAT4_H