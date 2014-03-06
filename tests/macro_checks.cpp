#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif

#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>

#include "macro_definitions.hpp"
#include "file_line_exception.hpp"


using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( macro_suite )

BOOST_AUTO_TEST_CASE ( line_macro )
{
  BOOST_MESSAGE("testing a few macro;");
  BOOST_CHECK_MESSAGE ( __LINE__ == atoi(STRING_LINE_NUMBER_(__LINE__)), "Failed conversion (const char *)->(int) using atoi");
  BOOST_CHECK_MESSAGE ( __LINE__ == boost::lexical_cast<size_t>(STRING__LINE__), "Failed conversion. Failed conversion (const char *)->(int) using boost::lexical_cast<size_t>");
  try
  {
    throw_line("test_throw_macro");
  }
  catch(file_line_runtime_error& in_error)
  {
    std::cout << in_error.what() << std::endl;
  }
}

BOOST_AUTO_TEST_SUITE_END()

