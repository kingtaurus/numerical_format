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


BOOST_AUTO_TEST_SUITE( symmetric_error_suite )

BOOST_AUTO_TEST_CASE ( symmetric_error_checks )
{
  BOOST_MESSAGE("Checking output of to_string_value and to_string_error");
}

BOOST_AUTO_TEST_SUITE_END()
