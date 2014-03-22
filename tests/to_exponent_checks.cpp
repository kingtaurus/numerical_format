#define BOOST_TEST_DYN_LINK

#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif


#include <boost/test/unit_test.hpp>
#include "macro_definitions.hpp"
#include "file_line_exception.hpp"
#include "error_helper_def.hpp"

BOOST_AUTO_TEST_SUITE( to_exponent_suite )

BOOST_AUTO_TEST_CASE ( exponent_test )
{
  double infinity = std::numeric_limits<double>::infinity();

  BOOST_MESSAGE("Checking output of exponent<double>;");
	BOOST_REQUIRE_EQUAL(exponent<double>(0.0000001), -7);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.000001), -6);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.00001), -5);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.0001), -4);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.001), -3);
  BOOST_REQUIRE_EQUAL(exponent<double>(0.01), -2);
  BOOST_REQUIRE_EQUAL(exponent<double>(0.1), -1);
  BOOST_REQUIRE_EQUAL(exponent<double>(1.), 0);
  BOOST_REQUIRE_EQUAL(exponent<double>(10.), 1);
  BOOST_REQUIRE_EQUAL(exponent<double>(100.), 2);
  BOOST_REQUIRE_EQUAL(exponent<double>(1000.), 3);
  BOOST_REQUIRE_EQUAL(exponent<double>(10000.), 4);
  BOOST_REQUIRE_EQUAL(exponent<double>(100000.), 5);
  BOOST_REQUIRE_EQUAL(exponent<double>(1000000.), 6);
  BOOST_REQUIRE_EQUAL(exponent<double>(10000000.), 7);
  BOOST_REQUIRE_EQUAL(exponent<double>(100000000.), 8);
  BOOST_REQUIRE_EQUAL(exponent<double>(1000000000.), 9);


	BOOST_REQUIRE_EQUAL(exponent<double>(0.0000009999999999), -6);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.000009999999999), -5);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.00009999999999), -4);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.0009999999999), -3);
	BOOST_REQUIRE_EQUAL(exponent<double>(0.009999999999), -2);
  BOOST_REQUIRE_EQUAL(exponent<double>(0.09999999999), -1);
  BOOST_REQUIRE_EQUAL(exponent<double>(0.9999999999), -0);
  BOOST_REQUIRE_EQUAL(exponent<double>(9.999999999), 1);
  BOOST_REQUIRE_EQUAL(exponent<double>(99.99999999), 2);
  BOOST_REQUIRE_EQUAL(exponent<double>(999.9999999), 3);
  BOOST_REQUIRE_EQUAL(exponent<double>(9999.999999), 4);
  BOOST_REQUIRE_EQUAL(exponent<double>(99999.99999), 5);
  BOOST_REQUIRE_EQUAL(exponent<double>(999999.9999), 6);
  BOOST_REQUIRE_EQUAL(exponent<double>(9999999.999), 7);
  BOOST_REQUIRE_EQUAL(exponent<double>(99999999.99), 8);
  BOOST_REQUIRE_EQUAL(exponent<double>(999999999.9), 9);
  BOOST_REQUIRE_EQUAL(exponent<double>(9999999999.99999), 10);

  BOOST_REQUIRE_THROW(exponent<double>(infinity), std::runtime_error);
}

BOOST_AUTO_TEST_CASE ( min_and_max_exponent_test )
{

  double infinity = std::numeric_limits<double>::infinity();

  BOOST_REQUIRE_EQUAL(to_string_max_exponent(0.0, 0.1), "0");
  BOOST_REQUIRE_EQUAL(to_string_max_exponent(0.1, 0.0), "0");
  BOOST_REQUIRE_EQUAL(to_string_max_exponent(0.1, 0.01),"-1");
  BOOST_REQUIRE_EQUAL(to_string_max_exponent(0.01,0.1), "-1");
  BOOST_REQUIRE_EQUAL(to_string_max_exponent(1.0, 0.1), "0");
  BOOST_REQUIRE_EQUAL(to_string_max_exponent(0.1, 1.1), "0");
  BOOST_REQUIRE_EQUAL(to_string_max_exponent(10.0, 0.1), "1");
  BOOST_REQUIRE_EQUAL(to_string_max_exponent(0.1, 10.1), "1");

  BOOST_REQUIRE_EQUAL(to_string_min_exponent(0.0, 0.1), "-1");
  BOOST_REQUIRE_EQUAL(to_string_min_exponent(0.1, 0.0), "-1");
  BOOST_REQUIRE_EQUAL(to_string_min_exponent(0.1, 0.01),"-2");
  BOOST_REQUIRE_EQUAL(to_string_min_exponent(0.01,0.1), "-2");
  BOOST_REQUIRE_EQUAL(to_string_min_exponent(1.0, 0.1), "-1");
  BOOST_REQUIRE_EQUAL(to_string_min_exponent(0.1, 1.1), "-1");
  BOOST_REQUIRE_EQUAL(to_string_min_exponent(10.0, 110.1), "1");
  BOOST_REQUIRE_EQUAL(to_string_min_exponent(110.1, 10.1), "1");

  BOOST_REQUIRE_EQUAL(maximum_exponent(0.0, 0.1),  0);
  BOOST_REQUIRE_EQUAL(maximum_exponent(0.1, 0.0),  0);
  BOOST_REQUIRE_EQUAL(maximum_exponent(0.1, 0.01),-1);
  BOOST_REQUIRE_EQUAL(maximum_exponent(0.01,0.1), -1);
  BOOST_REQUIRE_EQUAL(maximum_exponent(1.0, 0.1),  0);
  BOOST_REQUIRE_EQUAL(maximum_exponent(0.1, 1.1),  0);
  BOOST_REQUIRE_EQUAL(maximum_exponent(10.0, 0.1), 1);
  BOOST_REQUIRE_EQUAL(maximum_exponent(0.1, 10.1), 1);

  BOOST_REQUIRE_EQUAL(minimum_exponent(0.0, 0.1),   -1);
  BOOST_REQUIRE_EQUAL(minimum_exponent(0.1, 0.0),   -1);
  BOOST_REQUIRE_EQUAL(minimum_exponent(0.1, 0.01),  -2);
  BOOST_REQUIRE_EQUAL(minimum_exponent(0.01,0.1),   -2);
  BOOST_REQUIRE_EQUAL(minimum_exponent(1.0, 0.1),   -1);
  BOOST_REQUIRE_EQUAL(minimum_exponent(0.1, 1.1),   -1);
  BOOST_REQUIRE_EQUAL(minimum_exponent(10.0, 110.1), 1);
  BOOST_REQUIRE_EQUAL(minimum_exponent(110.1, 10.1), 1);


  BOOST_REQUIRE_THROW(to_string_min_exponent(0., infinity), std::runtime_error);
  BOOST_REQUIRE_THROW(to_string_min_exponent(infinity, 0.), std::runtime_error);
  BOOST_REQUIRE_THROW(maximum_exponent(0., infinity),       std::runtime_error);
  BOOST_REQUIRE_THROW(maximum_exponent(infinity, 0.),       std::runtime_error);
  BOOST_REQUIRE_THROW(minimum_exponent(0., infinity),       std::runtime_error);
  BOOST_REQUIRE_THROW(minimum_exponent(infinity, 0.),       std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

