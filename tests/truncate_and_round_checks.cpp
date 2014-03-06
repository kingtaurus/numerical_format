#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif


#include <boost/test/unit_test.hpp>
#include "macro_definitions.hpp"
#include "file_line_exception.hpp"
#include "error_helper_def.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( truncate_test_suite )

BOOST_AUTO_TEST_CASE (truncate_and_round_at_tests)
{
  BOOST_REQUIRE_CLOSE(round_at(0.123456, 0),     0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, 1),     0.1 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, 2),     0.12 ,    0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, 3),     0.123 ,   0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, 4),     0.1235 ,  0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, 5),     0.12346 , 0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, 6),     0.123456, 0.00001);

  BOOST_REQUIRE_CLOSE(round_at(0.123456, -1),    0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, -2),    0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, -3),    0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, -4),    0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, -5),    0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, -6),    0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(round_at(0.123456, -7),    0.0 ,     0.00001);

  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, 0),  0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, 1),  0.1 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, 2),  0.12 ,    0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, 3),  0.123 ,   0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, 4),  0.1234 ,  0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, 5),  0.12345 , 0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, 6),  0.123456 , 0.00001);

  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, -1), 0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, -2), 0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, -3), 0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, -4), 0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, -5), 0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, -6), 0.0 ,     0.00001);
  BOOST_REQUIRE_CLOSE(truncate_at(0.123456, -7), 0.0 ,     0.00001);

  //testing trucate_at
  //testing round_at
}

BOOST_AUTO_TEST_SUITE_END()

