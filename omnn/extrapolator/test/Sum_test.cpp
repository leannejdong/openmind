#define BOOST_TEST_MODULE Sum test
#include <boost/test/unit_test.hpp>

#include "Sum.h"
#include "Fraction.h"
#include "Variable.h"

BOOST_AUTO_TEST_CASE(Sum_tests)
{
    using namespace omnn::extrapolator;
    using s_t = Sum;
    using f_t = Fraction;
    Variable v;
    f_t f(1 , 2);
    f_t f1(5, 6);
    s_t a(1,2, f, 3) ;
    s_t b(6, f1);
    a -= b;
    a += Variable();
    std::cout << a;
}