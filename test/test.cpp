#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE my_unit_test
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <math/Vector.h>

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

    BOOST_AUTO_TEST_CASE(test) {
        iVec2 vec(1, 1);
        vec.x;
    }

BOOST_AUTO_TEST_SUITE_END()