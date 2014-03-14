#define BOOST_TEST_DYN_LINK

#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif

#include <boost/test/unit_test.hpp>
#include "macro_definitions.hpp"
#include "file_line_exception.hpp"
#include "error_helper_def.hpp"
#include "symmetric_error.hpp"

#include <iostream>

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


BOOST_FIXTURE_TEST_SUITE(multiple_error_checks, test_fixture)

BOOST_AUTO_TEST_CASE(check_error_throws_vector_empty)
{
  using namespace symmetric_error;
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1, {}), std::runtime_error);
  //make sure that an empty vector throws;
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1, {}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1, {}), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_error_throws_to_string_value_throw_checks)
{
  using namespace symmetric_error;
  //make sure that an infinity throws vector throws;
  BOOST_REQUIRE_THROW(to_string_value(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value(values.value_inf, errors.error_1), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_value(values.value_1, errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value(values.value_nan, errors.error_1), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_error_throws_to_string_value_output_checks)
{
  using namespace symmetric_error;

  //to_string_value(double,double)
  //make sure that an infinity throws vector throws;
  BOOST_REQUIRE_THROW(to_string_value(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value(values.value_inf, errors.error_1), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_value(values.value_1, errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value(values.value_nan, errors.error_1), std::runtime_error);
  //found a bunch of errors here: if the value would round up, 
  //then you have a problem (because you get an extra digit of precision)
  //

  BOOST_REQUIRE_EQUAL(to_string_value(1.0,0.01), "1.000");
  BOOST_REQUIRE_EQUAL(to_string_value(1.1,0.01), "1.100");
  BOOST_REQUIRE_EQUAL(to_string_value(1.2,0.01), "1.200");

  BOOST_REQUIRE_EQUAL(to_string_value(10.0,0.01), "1.0000");
  BOOST_REQUIRE_EQUAL(to_string_value(11.1,0.01), "1.1100");
  BOOST_REQUIRE_EQUAL(to_string_value(12.2,0.01), "1.2200");

  BOOST_REQUIRE_EQUAL(to_string_error(1.0,0.01), "0.010");
  BOOST_REQUIRE_EQUAL(to_string_error(1.1,0.01), "0.010");
  BOOST_REQUIRE_EQUAL(to_string_error(1.2,0.01), "0.010");

  BOOST_REQUIRE_EQUAL(to_string_error(10.0,0.01),  "0.0010");
  BOOST_REQUIRE_EQUAL(to_string_error(11.1,0.011), "0.0011");
  BOOST_REQUIRE_EQUAL(to_string_error(12.2,0.012), "0.0012");

  BOOST_REQUIRE_EQUAL(to_string_value(99.999,9.99), "1.00");
  BOOST_REQUIRE_EQUAL(to_string_error(99.999,9.99), "0.10");

  BOOST_REQUIRE_EQUAL(to_string_value(9.999,99.99), "0.10");
  BOOST_REQUIRE_EQUAL(to_string_error(9.999,99.99), "1.00");
                                     //99.999 +/- 9.99
                                     //99.999-> 100
                                     // 9.99 ->  10

  BOOST_REQUIRE_EQUAL(to_string_value(99.999,99.99), "1.0");
  BOOST_REQUIRE_EQUAL(to_string_error(99.999,99.99), "1.0");

  BOOST_REQUIRE_EQUAL(to_string_value(999.999,9.99), "1.000");
  BOOST_REQUIRE_EQUAL(to_string_error(999.999,9.99), "0.010");

  BOOST_REQUIRE_EQUAL(to_string_value(9.999,999.99), "0.010");
  BOOST_REQUIRE_EQUAL(to_string_error(9.999,999.99), "1.000");

}


BOOST_AUTO_TEST_CASE(check_to_string_exponent)
{
  using namespace symmetric_error;
  BOOST_REQUIRE_EQUAL(get_exponent(9.999,9.999),1);
}


BOOST_AUTO_TEST_CASE(check_get_max_exponent)
{
  using namespace symmetric_error;
  BOOST_REQUIRE_THROW(get_max_exponent({}), std::runtime_error);
  BOOST_REQUIRE_THROW(get_max_exponent({std::numeric_limits<double>::infinity()}), std::runtime_error);
  BOOST_REQUIRE_EQUAL(get_max_exponent({10000000.0}),7);
  BOOST_REQUIRE_EQUAL(get_max_exponent({1000000.00}),6);
  BOOST_REQUIRE_EQUAL(get_max_exponent({100000.000}),5);
  BOOST_REQUIRE_EQUAL(get_max_exponent({10000.0000}),4);
  BOOST_REQUIRE_EQUAL(get_max_exponent({1000.00000}),3);
  BOOST_REQUIRE_EQUAL(get_max_exponent({100.000000}),2);
  BOOST_REQUIRE_EQUAL(get_max_exponent({10.0000000}),1);
  BOOST_REQUIRE_EQUAL(get_max_exponent({1.00000000}),0);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.10000000}),-1);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.01000000}),-2);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.00100000}),-3);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.00010000}),-4);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.00001000}),-5);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.00000100}),-6);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.00000010}),-7);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.00000001}),-8);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0000000010}),-9);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0000000001}),-10);

  //rounding checks
  BOOST_REQUIRE_EQUAL(get_max_exponent({99999999.999}),8);
  BOOST_REQUIRE_EQUAL(get_max_exponent({9999999.9999}),7);
  BOOST_REQUIRE_EQUAL(get_max_exponent({999999.99999}),6);
  BOOST_REQUIRE_EQUAL(get_max_exponent({99999.999999}),5);
  BOOST_REQUIRE_EQUAL(get_max_exponent({9999.9999999}),4);
  BOOST_REQUIRE_EQUAL(get_max_exponent({999.99999999}),3);
  BOOST_REQUIRE_EQUAL(get_max_exponent({99.999999999}),2);
  BOOST_REQUIRE_EQUAL(get_max_exponent({9.9999999999}),1);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.9999999999}),0);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0999999999}),-1);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0099999999}),-2);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0009999999}),-3);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0000999999}),-4);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0000099999}),-5);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0000009999}),-6);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.0000000999}),-7);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.00000000999}),-8);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.000000000999}),-9);

  BOOST_REQUIRE_EQUAL(get_max_exponent({0.10, 0.01, 0.003, 0.0005}), -1);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.10, 0.01, 0.003, 0.003}),  -1);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.10, 0.01, 0.055, 0.0705}), -1);
  BOOST_REQUIRE_EQUAL(get_max_exponent({0.10, 99.01, 0.003, 0.0005}), 1);


}

BOOST_AUTO_TEST_CASE(check_to_string_min_exponent)
{
  using namespace symmetric_error;
  BOOST_REQUIRE_THROW(get_min_exponent({}), std::runtime_error);
  BOOST_REQUIRE_EQUAL(get_min_exponent({10000000.0}),7);
  BOOST_REQUIRE_EQUAL(get_min_exponent({1000000.00}),6);
  BOOST_REQUIRE_EQUAL(get_min_exponent({100000.000}),5);
  BOOST_REQUIRE_EQUAL(get_min_exponent({10000.0000}),4);
  BOOST_REQUIRE_EQUAL(get_min_exponent({1000.00000}),3);
  BOOST_REQUIRE_EQUAL(get_min_exponent({100.000000}),2);
  BOOST_REQUIRE_EQUAL(get_min_exponent({10.0000000}),1);
  BOOST_REQUIRE_EQUAL(get_min_exponent({1.00000000}),0);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.10000000}),-1);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.01000000}),-2);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.00100000}),-3);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.00010000}),-4);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.00001000}),-5);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.00000100}),-6);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.00000010}),-7);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.00000001}),-8);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0000000010}),-9);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0000000001}),-10);

  //rounding checks
  BOOST_REQUIRE_EQUAL(get_min_exponent({99999999.999}),8);
  BOOST_REQUIRE_EQUAL(get_min_exponent({9999999.9999}),7);
  BOOST_REQUIRE_EQUAL(get_min_exponent({999999.99999}),6);
  BOOST_REQUIRE_EQUAL(get_min_exponent({99999.999999}),5);
  BOOST_REQUIRE_EQUAL(get_min_exponent({9999.9999999}),4);
  BOOST_REQUIRE_EQUAL(get_min_exponent({999.99999999}),3);
  BOOST_REQUIRE_EQUAL(get_min_exponent({99.999999999}),2);
  BOOST_REQUIRE_EQUAL(get_min_exponent({9.9999999999}),1);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.9999999999}),0);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0999999999}),-1);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0099999999}),-2);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0009999999}),-3);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0000999999}),-4);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0000099999}),-5);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0000009999}),-6);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.0000000999}),-7);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.00000000999}),-8);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.000000000999}),-9);


  BOOST_REQUIRE_EQUAL(get_min_exponent({0.10, 0.01, 0.003, 0.0005}), -4);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.10, 0.01, 0.003, 0.003}),  -3);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.10, 0.01, 0.055, 0.0705}), -2);
  BOOST_REQUIRE_EQUAL(get_min_exponent({0.10, 99.01, 0.003, 0.0005}),-4);

}


BOOST_AUTO_TEST_CASE(check_error_throws_to_string_error)
{
  using namespace symmetric_error;

  BOOST_REQUIRE_THROW(to_string_error(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error(values.value_inf, errors.error_1), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_error(values.value_1, errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error(values.value_nan, errors.error_1), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(check_error_throws_to_string_value_fixed)
{
  using namespace symmetric_error;

  BOOST_REQUIRE_THROW(to_string_value_fixed(values.value_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value_fixed(values.value_inf, errors.error_1), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_value_fixed(values.value_1,   errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_value_fixed(values.value_nan, errors.error_1), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(check_error_throws_to_string_value_error)
{
  using namespace symmetric_error;

  BOOST_REQUIRE_THROW(to_string_error_fixed(values.value_1,   errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error_fixed(values.value_inf, errors.error_1), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_error_fixed(values.value_1,   errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_error_fixed(values.value_nan, errors.error_1), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(check_error_throws_to_tuple_multi_errors)
{
  using namespace symmetric_error;

  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_inf,               {errors.error_1}), std::runtime_error);
  //add more than one entry to the vector
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_1, errors.error_inf}), std::runtime_error);
  //add more than two entry to the vector
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_1, errors.error_2, errors.error_inf}), std::runtime_error);
  //add more than three entry to the vector
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_1, errors.error_2, errors.error_3, errors.error_inf}), std::runtime_error);

  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_nan,               {errors.error_1}), std::runtime_error);
  //add more than one entry to the vector
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_1, errors.error_nan}), std::runtime_error);
  //add more than two entry to the vector
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_1, errors.error_2, errors.error_nan}), std::runtime_error);
  //add more than three entry to the vector
  BOOST_REQUIRE_THROW(to_tuple_multi_errors(values.value_1,                 {errors.error_1, errors.error_2, errors.error_3, errors.error_nan}), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(check_error_throws_value_to_string_multiple_errors)
{
  using namespace symmetric_error;

  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_inf,     {errors.error_1}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_1, errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_1, errors.error_2, errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_1, errors.error_2, errors.error_3, errors.error_inf}), std::runtime_error);

  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_nan,     {errors.error_1}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_1, errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_1, errors.error_2, errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(value_to_string_multiple_errors(values.value_1,       {errors.error_1, errors.error_2, errors.error_3, errors.error_nan}), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(check_error_throws_to_string_multiple_errors_into_vector)
{
  using namespace symmetric_error;

  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_inf, {errors.error_1}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_1, errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_1, errors.error_2, errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_1, errors.error_2, errors.error_3, errors.error_inf}), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_nan, {errors.error_1}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_1, errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_1, errors.error_2, errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_multiple_errors_into_vector(values.value_1,   {errors.error_1, errors.error_2, errors.error_3, errors.error_nan}), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_error_throws_to_string_no_exponent)
{
  using namespace symmetric_error;

  //to_string_no_exponent(double,double)
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_inf, errors.error_1),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_inf, errors.error_inf), std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_nan, errors.error_1),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_nan, errors.error_nan), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_error_throws_to_string_no_exponent_three_parms)
{
  using namespace symmetric_error;

  //to_string_no_exponent(double,double,double)
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_1, errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_inf, errors.error_1), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_inf, errors.error_1, errors.error_2),   std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_1,   errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_nan, errors.error_1),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_nan, errors.error_1,   errors.error_2),   std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_error_throws_to_string_no_exponent_four_parms)
{
  using namespace symmetric_error;

  //to_string_no_exponent(double,double,double,double)
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_1,   errors.error_2,   errors.error_inf), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_1,   errors.error_inf, errors.error_2),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_inf, errors.error_1,   errors.error_2),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_inf, errors.error_1,   errors.error_2,   errors.error_3 ),  std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_1,   errors.error_2,   errors.error_nan), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_1,   errors.error_nan, errors.error_2),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_1,   errors.error_nan, errors.error_1,   errors.error_2),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent(values.value_nan, errors.error_1,   errors.error_2,   errors.error_3 ),  std::runtime_error);
}

BOOST_AUTO_TEST_CASE(check_error_throws_to_string_no_exponent_vector_parm)
{
  using namespace symmetric_error;

  //to_string_no_exponent(std::vector<double>)
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_1,   errors.error_2,   errors.error_inf}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_1,   errors.error_inf,   errors.error_2}),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_inf,   errors.error_2,   errors.error_3}),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_inf,   errors.error_1,   errors.error_2,   errors.error_3} ),  std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_no_exponent({}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_inf,   errors.error_1}),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_inf,   errors.error_2}),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_1,     errors.error_2,   errors.error_3, errors.error_inf} ),  std::runtime_error);

  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_1,   errors.error_2,   errors.error_nan}), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_1,   errors.error_nan,   errors.error_2}),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_1,   errors.error_nan,   errors.error_2,   errors.error_3}),   std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_no_exponent({values.value_nan,   errors.error_1,   errors.error_2,   errors.error_3} ),  std::runtime_error);
}


BOOST_AUTO_TEST_SUITE_END()
