#define BOOST_TEST_DYN_LINK

#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "macro_definitions.hpp"
#include "file_line_exception.hpp"
#include "error_helper_def.hpp"
#include "symmetric_error.hpp"
#include "stream_output_proxy.hpp"


BOOST_AUTO_TEST_CASE ( stream_output_checks )
{
  BOOST_MESSAGE("Checking output of stream output functionality");
  std::cout << eoc << 1.2 << std::endl;
  std::cout << leoc<< 0.4 << std::endl;
  std::cout << eoc << std::pair<double,double>(1.2,0.4) << std::endl;
}

