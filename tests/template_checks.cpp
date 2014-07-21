#define BOOST_TEST_DYN_LINK

#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Main
#endif


#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <boost/chrono/chrono.hpp>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/mpfr.hpp>

#include <type_traits>

namespace std
{
  template <>
  class is_floating_point<boost::multiprecision::cpp_dec_float_50> :
    public std::integral_constant<bool,true>{};

  template <>
  class is_floating_point<boost::multiprecision::mpfr_float_50> :
    public std::integral_constant<bool,true>{};

  template <>
  class is_floating_point<boost::multiprecision::mpf_float_50> :
    public std::integral_constant<bool,true>{};
}

#include "error_helper_def.hpp"

using namespace boost::unit_test;
namespace bm = boost::multiprecision;
typedef boost::mpl::list<double, long double, bm::cpp_dec_float_50> test_types;

BOOST_AUTO_TEST_SUITE( template_check_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE ( numeric_limits_output, T, test_types )
{
  BOOST_MESSAGE("digits   = " << std::numeric_limits<T>::digits);
  BOOST_MESSAGE("digits10 = " << std::numeric_limits<T>::digits10);

  BOOST_CHECK_GT(std::numeric_limits<T>::digits,   std::numeric_limits<float>::digits);
  BOOST_CHECK_GT(std::numeric_limits<T>::digits10, std::numeric_limits<float>::digits10);
  BOOST_CHECK(std::numeric_limits<T>::has_infinity);
  BOOST_CHECK(std::numeric_limits<T>::has_quiet_NaN);
  BOOST_CHECK(!(std::numeric_limits<T>::has_denorm_loss));

  BOOST_CHECK(std::numeric_limits<T>::is_bounded);
  BOOST_CHECK(!(std::numeric_limits<T>::is_modulo));
  BOOST_WARN(std::numeric_limits<T>::round_style == std::float_round_style::round_indeterminate);//bm::cpp_dec_float_50
  BOOST_WARN(std::numeric_limits<T>::round_style == std::float_round_style::round_to_nearest);//double, long double

  BOOST_CHECK(std::is_floating_point<T>::value);
}

BOOST_AUTO_TEST_SUITE_END()
