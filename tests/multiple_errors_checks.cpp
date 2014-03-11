#define BOOST_TEST_DYN_LINK

#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif

#include <boost/test/unit_test.hpp>
#include "macro_definitions.hpp"
#include "file_line_exception.hpp"
#include "error_helper_def.hpp"
#include "symmetric_error.hpp"

using namespace boost::unit_test;

//std::numeric_limits<double>::infinity()
//std::numeric_limits<double>::quiet_NaN()
//std::numeric_limits<double>::signaling_NaN()
//signaling_NaN() gets trapped by CTest
//



//The following shows how signaling handling is done:
//#include <signal.h>
//#include <stdio.h>
//#include <stdlib.h>
// 
//static void catch_function(int signo) {
//    puts("Interactive attention signal caught.");
//}
// 
//int main(void) {
//    if (signal(SIGINT, catch_function) == SIG_ERR) {
//        fputs("An error occurred while setting a signal handler.\n", stderr);
//        return EXIT_FAILURE;
//    }
//    puts("Raising the interactive attention signal.");
//    if (raise(SIGINT) != 0) {
//        fputs("Error raising the signal.\n", stderr);
//        return EXIT_FAILURE;
//    }
//    puts("Exiting.");
//    return 0;
//}

struct test_values
{
  double value_1;
  double value_2;
  double value_3;
  double value_4;
  double value_5;
  double value_6;
  double value_7;
  double value_8;
  double value_9;
  double value_inf;
  double value_nan;
  test_values() : 
    value_1(99.9),
    value_2( 9.9),
    value_3( 0.99),
    value_4( 0.099),
    value_5( 0.0099),
    value_6( 0.000999),
    value_7( 0.0000999),
    value_8( 0.00000999),
    value_9( 0.000000999),
    value_inf(std::numeric_limits<double>::infinity()),
    value_nan(std::numeric_limits<double>::quiet_NaN())
  {
    BOOST_TEST_MESSAGE("setup values;");
  }
  ~test_values() 
  {
    BOOST_TEST_MESSAGE("teardown values;");
  }
};

struct test_errors
{
  double error_1;
  double error_2;
  double error_3;
  double error_4;
  double error_5;
  double error_6;
  double error_7;
  double error_8;
  double error_9;
  double error_inf;
  double error_nan;
  test_errors() : 
    error_1(99.99),
    error_2( 9.99),
    error_3( 0.999),
    error_4( 0.0999),
    error_5( 0.00999),
    error_6( 0.000999),
    error_7( 0.0000999),
    error_8( 0.00000999),
    error_9( 0.000000999),
    error_inf(std::numeric_limits<double>::infinity()),
    error_nan(std::numeric_limits<double>::quiet_NaN())
  {
    BOOST_TEST_MESSAGE("setup errors;");
  }
  ~test_errors() 
  {
    BOOST_TEST_MESSAGE("teardown errors;");
  }
};

struct test_fixture
{
  test_values  values;
  test_errors  errors;

  test_fixture ()
    : values(), 
      errors()
  {
    BOOST_TEST_MESSAGE("setup test_fixture;");
  }
  ~test_fixture()
  {
    BOOST_TEST_MESSAGE("teardown test_fixture;");
  }
};


BOOST_FIXTURE_TEST_SUITE(multiple_error_checks, test_fixture)

BOOST_AUTO_TEST_CASE(check_error_throws_vector_empty)
{
  using namespace symmetric_error;

  BOOST_TEST_MESSAGE("check_one");
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1, {}), std::runtime_error);
  //make sure that an empty vector throws;
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1, {}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1, {}), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_error_throws_inf)
{
  using namespace symmetric_error;

//to_string_value(double,double)
//to_string_error(double,double)
//to_string_value_fixed(double,double)
//to_string_error_fixed(double,double)
//to_tuple_multi_errors(double,vector)
//value_to_string_multiple_errors(double,vector)
//to_string_multiple_errors_into_vector(double,vector)
//to_string_no_exponent(double,double)
//to_string_no_exponent(std::vector)
//to_string_no_exponent(double,double,double)
//to_string_no_exponent(double,double,double,double)

  BOOST_TEST_MESSAGE("check_one");
  BOOST_REQUIRE_THROW(to_string_value(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value(values.value_inf, errors.error_1), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error(values.value_inf, errors.error_1), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_value_fixed(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value_fixed(values.value_inf, errors.error_1), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error_fixed(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error_fixed(values.value_inf, errors.error_1), std::runtime_error);




  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1, {errors.error_inf}), std::runtime_error);
  //make sure that an empty vector throws;
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1, {errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1, {errors.error_inf}), std::runtime_error);

  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_inf, {errors.error_inf}), std::runtime_error);
  //make sure that an empty vector throws;
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_inf, {errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_inf, {errors.error_inf}), std::runtime_error);



}


BOOST_AUTO_TEST_SUITE_END()
