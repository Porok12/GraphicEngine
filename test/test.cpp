#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE main
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <math/Vec2.h>
#include <math/Vec3.h>
#include <math/Mat4.h>

BOOST_AUTO_TEST_SUITE(math_ivec2_suite)

    BOOST_AUTO_TEST_CASE(init_values) {
        iVec2 vec;
        BOOST_CHECK_EQUAL(vec.x, 0);
        BOOST_CHECK_EQUAL(vec.y, 0);
    }

    BOOST_AUTO_TEST_CASE(change_x) {
        iVec2 vec;
        vec.x = 2;
        BOOST_CHECK_EQUAL(vec.x, 2);
    }

    BOOST_AUTO_TEST_CASE(change_y) {
        iVec2 vec;
        vec.y = 3;
        BOOST_CHECK_EQUAL(vec.y, 3);
    }

    BOOST_AUTO_TEST_CASE(bracket) {
        iVec2 vec(2, 1);
        vec.x = 3;
        BOOST_CHECK_EQUAL(vec.x, vec[0]);
        BOOST_CHECK_EQUAL(vec.y, vec[1]);
    }

    BOOST_AUTO_TEST_CASE(addition) {
        iVec2 vec1(1, 2);
        iVec2 vec2(2, 1);
        vec1 += vec2;
        BOOST_CHECK_EQUAL(vec1.x, 3);
        BOOST_CHECK_EQUAL(vec1.y, 3);
    }

    BOOST_AUTO_TEST_CASE(subtraction) {
        iVec2 vec1(1, 2);
        iVec2 vec2(2, 1);
        iVec2 vec = vec1 - vec2;
        BOOST_CHECK_EQUAL(vec.x, -1);
        BOOST_CHECK_EQUAL(vec.y, 1);
    }

    BOOST_AUTO_TEST_CASE(subtraction2) {
        iVec2 vec1(1, 2);
        iVec2 vec2(2, 1);
        iVec2 vec = vec1 - vec2;
        vec.x += 1;
        vec[1] -= 1;
        BOOST_CHECK_EQUAL(vec[0], 0);
        BOOST_CHECK_EQUAL(vec.y, 0);
    }

    BOOST_AUTO_TEST_CASE(multiply1) {
        iVec2 vec1(1, 2);
        iVec2 vec2(2, 1);
        iVec2 vec = vec1 * vec2;
        BOOST_CHECK_EQUAL(vec[0], 2);
        BOOST_CHECK_EQUAL(vec.y, 2);
    }

    BOOST_AUTO_TEST_CASE(multiply2) {
        iVec2 vec1(1, 2);
        iVec2 vec = vec1 * 2;
        BOOST_CHECK_EQUAL(vec[0], 2);
        BOOST_CHECK_EQUAL(vec.y, 4);
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(math_fvec2_suite)

    BOOST_AUTO_TEST_CASE(normalize) {
        fVec2 vec(1.0f, 1.0f);
        vec.normalize();
        BOOST_CHECK_CLOSE((float) vec.x, 0.707106781186548f, 0.01);
        BOOST_CHECK_CLOSE((float) vec.y, 0.707106781186548f, 0.01);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(math_fvec3_suite)

    BOOST_AUTO_TEST_CASE(assigment) {
        fVec3 vec1(2, 2, 2);
        fVec3 vec2 = vec1;
        vec2.x = 1;
        vec2[1] = 1;
        vec2.z = 1;

        BOOST_CHECK_CLOSE((float)vec1.x, 2, 0.01);
        BOOST_CHECK_CLOSE((float)vec1.y, 2, 0.01);
        BOOST_CHECK_CLOSE((float)vec1.z, 2, 0.01);

        BOOST_CHECK_CLOSE(vec1[0], 2, 0.01);
        BOOST_CHECK_CLOSE(vec1[1], 2, 0.01);
        BOOST_CHECK_CLOSE(vec1[2], 2, 0.01);

        BOOST_CHECK_CLOSE((float)vec2.x, 1, 0.01);
        BOOST_CHECK_CLOSE((float)vec2.y, 1, 0.01);
        BOOST_CHECK_CLOSE((float)vec2.z, 1, 0.01);

        BOOST_CHECK_CLOSE(vec2[0], 1, 0.01);
        BOOST_CHECK_CLOSE(vec2[1], 1, 0.01);
        BOOST_CHECK_CLOSE(vec2[2], 1, 0.01);
    }

    BOOST_AUTO_TEST_CASE(dot_product) {
        fVec3 vec1(1, 3, -5);
        fVec3 vec2(4, -2, -1);
        float f = vec1.dot(vec2);
        BOOST_CHECK_CLOSE(f, 3.0f, 0.01);
    }

    BOOST_AUTO_TEST_CASE(cross_product) {
        fVec3 vec1(1, 2, 3);
        fVec3 vec2(1, 5, 7);
        fVec3 vec = vec1.cross(vec2);
        BOOST_CHECK_CLOSE((float) vec.x, -1.0f, 0.01);
        BOOST_CHECK_CLOSE((float) vec.y, -4.0f, 0.01);
        BOOST_CHECK_CLOSE((float) vec.z, 3.0f, 0.01);

        BOOST_CHECK_CLOSE(vec[0], -1.0f, 0.01);
        BOOST_CHECK_CLOSE(vec[1], -4.0f, 0.01);
        BOOST_CHECK_CLOSE(vec[2], 3.0f, 0.01);
    }

    BOOST_AUTO_TEST_CASE(cross_product2) {
        fVec3 vec1(2, 1, -1);
        fVec3 vec2(-3, 4, 1);
        fVec3 vec = vec1.cross(vec2);
        BOOST_CHECK_CLOSE((float) vec.x, 5, 0.01);
        BOOST_CHECK_CLOSE((float) vec.y, 1, 0.01);
        BOOST_CHECK_CLOSE((float) vec.z, 11, 0.01);

        BOOST_CHECK_CLOSE(vec[0], 5, 0.01);
        BOOST_CHECK_CLOSE(vec[1], 1, 0.01);
        BOOST_CHECK_CLOSE(vec[2], 11, 0.01);
    }

BOOST_AUTO_TEST_SUITE_END()

//-------------------------------------------------------

BOOST_AUTO_TEST_SUITE(math_mat4_suitex)

    BOOST_AUTO_TEST_CASE(get) {
        Mat4 mat;
        mat[0][0] = 1;
        float x1 = mat[0][0];
        mat[loc(0, 0)] = 2;
        float x2 = mat[loc(0, 0)];
        BOOST_CHECK_CLOSE(x1, 1, 0.1);
        BOOST_CHECK_CLOSE(x2, 2, 0.1);
    }

    BOOST_AUTO_TEST_CASE(projection) {
        Mat4 mat = Mat4::getProjection(90.0f, 4.0f/3.0f, 0.1f, 1000.0f);

        double precision = 2.0;
        BOOST_CHECK_CLOSE(mat[loc(0, 0)], 0.75, precision);
        BOOST_CHECK_CLOSE(mat[loc(1, 1)], 1.0, precision);
        BOOST_CHECK_CLOSE(mat[loc(2, 2)], -1.00, precision);
        BOOST_CHECK_CLOSE(mat[loc(3, 2)], -0.200, precision);
        BOOST_CHECK_CLOSE(mat[loc(2, 3)], -1.0, precision);
    }

    BOOST_AUTO_TEST_CASE(translation) {
        Mat4 tra = Mat4::translate(1, 2, 3);
        Mat4 mat;
        mat[0][0] = 1; mat[1][1] = 1; mat[2][2] = 1; mat[3][3] = 1;
        mat[3][0] = 1; mat[3][1] = 2; mat[3][2] = 3;

        for (int m = 0; m < 4; ++m) {
            for (int n = 0; n < 4; ++n) {
                BOOST_CHECK_CLOSE(mat[m][n], tra[m][n], 0.01);
            }
        }
    }

    BOOST_AUTO_TEST_CASE(lookAt) {
        fVec3 eye(0, -10, 50);
        fVec3 target(0, 1, -50);
        Mat4 mat = Mat4::lookAt(eye, target);

        double precision = 2.0; //%
        BOOST_CHECK_CLOSE(mat[loc(0, 0)], 0.994, precision);
        BOOST_CHECK_CLOSE(mat[loc(1, 1)], 0.988, precision);
        BOOST_CHECK_CLOSE(mat[loc(2, 2)], 0.994, precision);
        BOOST_CHECK_CLOSE(mat[loc(3, 3)], 1.000, precision);
        BOOST_CHECK_CLOSE(mat[loc(2, 1)], -0.109, precision);
        BOOST_CHECK_CLOSE(mat[loc(1, 2)], 0.108, precision);
        BOOST_CHECK_CLOSE(mat[loc(1, 3)], 4.446, precision);
        BOOST_CHECK_CLOSE(mat[loc(2, 3)], -50.793, precision);
    }

    BOOST_AUTO_TEST_CASE(multiply) {
        Mat4 mat1, mat2;

        for (int m = 0; m < 4; ++m) {
            for (int n = 0; n < 4; ++n) {
                mat1[m][n] = (m+n)%2 ? 0 : 1;
                mat2[m][n] = (m+n)%2 ? 1 : 0;
            }
        }

        Mat4 mat = mat1 * mat2;

        double precision = 0.1; //%
        for (int m = 0; m < 4; ++m) {
            for (int n = 0; n < 4; ++n) {
                BOOST_CHECK_CLOSE(mat[loc(m, n)], 0, precision);
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()
