#define BOOST_TEST_DYN_LINK

#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "macro_definitions.hpp"
#include "file_line_exception.hpp"
#include "error_helper_def.hpp"

using namespace boost::unit_test;
namespace bm = boost::multiprecision;


//TODO convert to a fixture testing
BOOST_AUTO_TEST_SUITE( fixed_string_suite )
BOOST_AUTO_TEST_CASE ( to_fixed_string_test_default_double )
{
  BOOST_MESSAGE("Checking output of to_fixed_string<double>; default prec[=2]");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0),        "0.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.001),    "0.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.01),     "0.01");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.1),      "0.10");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(1.0),      "1.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(10.0),     "10.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(100.0),    "100.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(1000.0),   "1000.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.009999), "0.01");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.009998), "0.01");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.00998),  "0.01");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.0098),   "0.01");

  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.005),    "0.01");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.004999), "0.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.04999),  "0.05");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.4999),   "0.50");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(4.999),    "5.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(49.999),   "50.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(499.99),   "499.99");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(499.999),  "500.00");

  BOOST_REQUIRE_THROW( to_fixed_string<double>(std::numeric_limits<double>::infinity()), std::runtime_error);
  std::cout <<  to_fixed_string<double>(499.999) << std::endl;
}

BOOST_AUTO_TEST_CASE ( to_fixed_string_test_prec_double )
{
  BOOST_MESSAGE("Checking output of to_fixed_string<double>; default prec[=<x>]");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.001,3),      "0.001");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.001,0),      "0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(101.234,0),    "101");

  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.0101234, 3), "0.010");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(0.001,4),      "0.0010");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(12.,2),        "12.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(12.,1),        "12.0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(12.,0),        "12");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(125.,0),       "125");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(125.,6),       "125.000000");

  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(123456,-1),    "123460");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(123456,-2),    "123500");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(123456,-3),    "123000");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(123456,-4),    "120000");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(123456,-5),    "100000");
  BOOST_REQUIRE_EQUAL( to_fixed_string<double>(123456,-6),    "0");
}

BOOST_AUTO_TEST_CASE ( to_fixed_string_test_prec_long_double )
{
  BOOST_MESSAGE("Checking output of to_fixed_string<long double>; default prec[=<x>]");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(0.001,3),      "0.001");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(0.001,0),      "0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(101.234,0),    "101");

  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(0.0101234, 3), "0.010");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(0.001,4),      "0.0010");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(12.,2),        "12.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(12.,1),        "12.0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(12.,0),        "12");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(125.,0),       "125");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(125.,6),       "125.000000");

  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(123456,-6),    "0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(123456,-1),    "123460");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(123456,-2),    "123500");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(123456,-3),    "123000");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(123456,-4),    "120000");
  BOOST_REQUIRE_EQUAL( to_fixed_string<long double>(123456,-5),    "100000");

  BOOST_REQUIRE_THROW( to_fixed_string<long double>(std::numeric_limits<long double>::infinity(),0), std::runtime_error);
}

BOOST_AUTO_TEST_CASE ( to_fixed_string_test_prec_cpp_dec )
{
  BOOST_MESSAGE("Checking output of to_fixed_string<bm::cpp_dec_float_50>; default prec[=<x>]");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(bm::cpp_dec_float_50(0.001),3),      "0.001");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(0.001,0),      "0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(101.234,0),    "101");

  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(0.0101234, 3), "0.010");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(0.001,4),      "0.0010");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(12.,2),        "12.00");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(12.,1),        "12.0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(12.,0),        "12");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(125.,0),       "125");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(125.,6),       "125.000000");

  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(123456,-6),    "0");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(123456,-1),    "123460");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(123456,-2),    "123500");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(123456,-3),    "123000");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(123456,-4),    "120000");
  BOOST_REQUIRE_EQUAL( to_fixed_string<bm::cpp_dec_float_50>(123456,-5),    "100000");

  BOOST_REQUIRE_THROW( to_fixed_string<bm::cpp_dec_float_50>(std::numeric_limits<long double>::infinity(),0), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
