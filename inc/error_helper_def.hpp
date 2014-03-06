#ifndef ERROR_HELPER_DEF_HPP
#define ERROR_HELPER_DEF_HPP

#include <type_traits>

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/lexical_cast.hpp>
#include <stdexcept>

#include "macro_definitions.hpp"

extern double truncate_at(const double& in_value, int decimal_point);
extern double round_at   (const double& in_value, int decimal_point);
extern int    maximum_exponent(const double value_1, const double value_2);
extern int    minimum_exponent(const double value_1, const double value_2);

extern std::string
to_string_max_exponent(const double value_1, const double value_2);
extern std::string
to_string_min_exponent(const double value_1, const double value_2);



template <typename T>
std::string to_fixed_string(const T& in_type, const int precision = 2)
{
  std::string in_function = __PRETTY_FUNCTION__;
  if (std::is_floating_point<T>::value && boost::math::isinf(in_type))
  {
    throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);//double expand this macro will make this a c-string
  }
  std::stringstream to_string;
  to_string.setf(std::ios::fixed);
  if (precision == 0 )
  {
    to_string.unsetf(std::ios::showpoint);
  }
  else
  {
    to_string.setf(std::ios::showpoint);
  }
  to_string.precision(precision);
  to_string << in_type;
  return to_string.str();
}

//full specialization
template <>
std::string to_fixed_string(const double & in_type, const int precision);


template <typename T>
inline 
std::string to_sci_string(const T & in_decimal, const int in_precision = 2)
{
  std::string in_function = __PRETTY_FUNCTION__;
  if (std::is_floating_point<T>::value && boost::math::isinf(in_decimal))
  {
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
std::string to_sci_string_max_prec(const T & in_decimal)
{
  std::string in_function = __PRETTY_FUNCTION__;
  if (std::is_floating_point<T>::value && boost::math::isinf(in_decimal))
  {
    throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);//double expand this macro will make this a c-string
  }
  std::stringstream to_string;
	to_string.setf(std::ios::scientific | std::ios::showpoint);
  to_string.precision(std::numeric_limits<T>::digits10);
  to_string << in_decimal;
	return to_string.str();
}

template <typename T>
inline int exponent(const T & in_value) throw(std::runtime_error)
{
  std::string exponential = to_sci_string<T>(in_value,1);
	std::string number = exponential.substr(exponential.find_last_of("Ee") + 1, std::string::npos);
	return boost::lexical_cast<int>(number);
}

template <typename T>
inline double decimal_representation(const T & in_decimal)
{
  std::string a_string = to_sci_string_max_prec<T>(in_decimal);
	a_string.erase(a_string.find_first_of("Ee"), std::string::npos);
	return boost::lexical_cast<double>(a_string);//can bad_lexical_cast
}

template <typename T>
inline
std::string two_digits(const T & in_decimal)
{
	std::string two_digits = to_sci_string(in_decimal,1);
	two_digits.erase(two_digits.find_first_of("Ee"), std::string::npos);
	return two_digits;
}

template <typename T>
inline double two_digits_as_double(const T & in_decimal)
{
  //alternate round_at(going_to_specific_double, -exponent<double>(going_to_specific_double + 2);
	return boost::lexical_cast<double>(two_digits<T>(in_decimal));
}







#endif
