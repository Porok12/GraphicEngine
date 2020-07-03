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
//        iVec2 vec = vec1 + vec2;
        vec1 += vec2;
        BOOST_CHECK_EQUAL(vec1.x, 3);
        BOOST_CHECK_EQUAL(vec1.y, 3);



        [] {
            ;
        }();

        auto lmda = [] {
            ;
        };

        lmda();
}

    BOOST_AUTO_TEST_CASE(subtraction) {
        iVec2 vec1(1, 2);
        iVec2 vec2(2, 1);
        iVec2 vec = vec1 - vec2;
        BOOST_CHECK_EQUAL(vec.x, -1);
        BOOST_CHECK_EQUAL(vec.y, 1);
    }

    BOOST_AUTO_TEST_CASE(test) {
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

BOOST_AUTO_TEST_CASE(test) {
        fVec2 vec(1.0f, 1.0f);
        vec.normalize();
        BOOST_CHECK_CLOSE((float)vec.x, 0.707106781186548f, 0.01);
        BOOST_CHECK_CLOSE((float)vec.y, 0.707106781186548f, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(math_fvec3_suite)

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
        BOOST_CHECK_CLOSE((float)vec.x, -1.0f, 0.01);
        BOOST_CHECK_CLOSE((float)vec.y, -4.0f, 0.01);
        BOOST_CHECK_CLOSE((float)vec.z, 3.0f, 0.01);

        BOOST_CHECK_CLOSE(vec[0], -1.0f, 0.01);
        BOOST_CHECK_CLOSE(vec[1], -4.0f, 0.01);
        BOOST_CHECK_CLOSE(vec[2], 3.0f, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()

//-------------------------------------------------------

BOOST_AUTO_TEST_SUITE(math_mat4_suitex)

BOOST_AUTO_TEST_CASE(xxxxx) {
        Mat4 mat;
        mat[0][0] = 1;
        float x1 = mat[0][0];
        mat[loc(0, 0)] = 2;
        float x2 = mat[loc(0, 0)];
        std::cerr << x1 << " " << x2 << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
