#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE my_unit_test
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

//...

BOOST_AUTO_TEST_SUITE(my_testsuite)

BOOST_AUTO_TEST_CASE(case_one) {
    BOOST_CHECK_EQUAL(0, 0);
}

BOOST_AUTO_TEST_SUITE_END()