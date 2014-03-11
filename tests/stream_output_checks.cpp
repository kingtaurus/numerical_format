#define BOOST_TEST_DYN_LINK

#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif

#include <boost/test/unit_test.hpp>
#include "macro_definitions.hpp"
#include "file_line_exception.hpp"
#include "error_helper_def.hpp"
#include "stream_output_proxy.hpp"

BOOST_AUTO_TEST_SUITE( stream_output_suite )

BOOST_AUTO_TEST_CASE ( stream_output_checks )
{
  BOOST_MESSAGE("Checking output of stream output functionality");
}

BOOST_AUTO_TEST_SUITE_END()
