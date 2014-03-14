#ifndef ERROR_HELPER_DEF_HPP
#define ERROR_HELPER_DEF_HPP

#include <type_traits>

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/powm1.hpp>
#include <boost/lexical_cast.hpp>
#include <stdexcept>

#include "macro_definitions.hpp"

extern double truncate_at(const double& in_value, int decimal_point);
extern long double truncate_at(const long double& in_value, int decimal_point);

extern double round_at   (const double& in_value, int decimal_point);
extern long double round_at (const long double& in_value, int decimal_point);
extern float round_at(const float& in_value, int decimal_point);

extern int    maximum_exponent(const double value_1, const double value_2);
extern int    minimum_exponent(const double value_1, const double value_2);

extern std::string
to_string_max_exponent(const double value_1, const double value_2);
extern std::string
to_string_min_exponent(const double value_1, const double value_2);

template<typename T>
T round_at(const T& in_decimal, int decimal_point = 0)
{
  namespace bmath = boost::math;
  T power = bmath::powm1(T(10.), decimal_point) + T(1.0);
  return bmath::round(in_decimal * power) / power;
}

template <typename T>
std::string to_fixed_string(const T& in_type, const int in_precision = 2)
{
  if (std::is_floating_point<T>::value && boost::math::isinf(in_type))
  {
    std::string in_function = __PRETTY_FUNCTION__;
    throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);//double expand this macro will make this a c-string
  }
  std::stringstream to_string;
  to_string.setf(std::ios::fixed);
  if (in_precision <= 0 )
  {
    to_string.unsetf(std::ios::showpoint);
    to_string.precision(0);
    //this can be dangerous (this will create a long double)
    // less precision than boost::multiprecision::cpp_dec_float_50
    //
    //should lose precision
    long double rounded(round_at(in_type, in_precision));
    to_string << rounded;
    return to_string.str();
  }
  else
  {
    to_string.setf(std::ios::showpoint);
    to_string.precision(in_precision);
  }
  to_string << in_type;
  return to_string.str();
}

//full specialization
template <>
std::string to_fixed_string(const double & in_type, const int precision);


template <typename T>
inline
std::string to_sci_string(const T & in_decimal, const int in_precision = 1) throw(std::runtime_error)
{
  if (std::is_floating_point<T>::value && (boost::math::isinf(in_decimal) || boost::math::isnan(in_decimal)))
  {
    std::string in_function = __PRETTY_FUNCTION__;
    throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);//double expand this macro will make this a c-string
  }
  std::stringstream to_string;
  to_string.setf(std::ios::scientific | std::ios::showpoint);
  to_string.precision(in_precision);
  to_string << in_decimal;
  return to_string.str();
}

template <typename T>
inline
std::string to_sci_string_max_prec(const T & in_decimal) throw(std::runtime_error)
{
  if (std::is_floating_point<T>::value && (boost::math::isinf(in_decimal) || boost::math::isnan(in_decimal)) )
  {
    std::string in_function = __PRETTY_FUNCTION__;
    throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);//double expand this macro will make this a c-string
  }
  std::stringstream to_string;
	to_string.setf(std::ios::scientific | std::ios::showpoint);
  to_string.precision(std::numeric_limits<T>::digits10);
  to_string << in_decimal;
	return to_string.str();
}

//template <typename T>
//inline int exponent(const T & in_value) throw(std::runtime_error)
//{
//  std::string exponential = to_sci_string<T>(in_value,1);
//	std::string number = exponential.substr(exponential.find_last_of("Ee") + 1, std::string::npos);
//	return boost::lexical_cast<int>(number);
//}

template <typename T>
inline int exponent(const T & in_value, const int in_precision = 1)
{
  std::string exponential = to_sci_string<T>(in_value,in_precision);
	std::string number = exponential.substr(exponential.find_last_of("Ee") + 1, std::string::npos);
	return boost::lexical_cast<int>(number);
}

template <typename T>
inline int exponent_max_prec(const T & in_value)
{
  std::string exponential = to_sci_string<T>(in_value,std::numeric_limits<T>::digits10);
	std::string number = exponential.substr(exponential.find_last_of("Ee") + 1, std::string::npos);
	return boost::lexical_cast<int>(number);
}

template <typename T>
inline double decimal_representation_max_prec(const T & in_decimal)
{
  std::string a_string = to_sci_string_max_prec<T>(in_decimal);
	a_string.erase(a_string.find_first_of("Ee"), std::string::npos);
	return boost::lexical_cast<double>(a_string);//can bad_lexical_cast
}

template <typename T>
inline double decimal_representation(const T & in_decimal, const int in_precision = 1)
{
  std::string out_string = to_sci_string(in_decimal, in_precision);
  out_string.erase(out_string.find_first_of("Ee"), std::string::npos);
  return boost::lexical_cast<double>(out_string);
}

template <typename T>
inline
std::string two_digits(const T & in_decimal)
{
  return boost::lexical_cast<std::string>(decimal_representation(in_decimal, 1));
}

template <typename T>
inline double two_digits_double(const T & in_decimal)
{
  //alternate round_at(going_to_specific_double, -exponent<double>(going_to_specific_double + 2);
	return decimal_representation(in_decimal,1);
}







#endif
