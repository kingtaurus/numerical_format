#include "error_helper_def.hpp"
#include <cmath>

double truncate_at(const double& in_value, int decimal_point = 0)
{
  return std::trunc(in_value * std::pow(10.,decimal_point)) * std::pow (10.,-decimal_point);
}
//this takes a double: xyz.abcd -> shifts the decimal_point (if positive it makes the number larger)
// so: truncate_at(xyz.abcd)    |-> xyz           ,
//     truncate_at(xyz.abcd,-1) |-> xy.zabc |-> xy,

long double truncate_at(const long double& in_value, int decimal_point = 0 )
{
  return std::trunc(in_value * std::pow(10.,decimal_point)) * std::pow (10.,-decimal_point);
}
//this takes a double: xyz.abcd -> shifts the decimal_point (if positive it makes the number larger)
// so: truncate_at(xyz.abcd)    |-> xyz           ,
//     truncate_at(xyz.abcd,-1) |-> xy.zabc |-> xy,

float round_at(const float& in_value, int decimal_point = 0)
{
  return std::round(in_value * std::pow(10.f,float(decimal_point))) * std::pow (10.f, -float(decimal_point));//
  //this takes a double: xyz.abcd -> shifts the decimal_point (if positive it makes the number larger)
  // so: round_at(xyz.abcd)    |-> xy|z|           , where |z| is rounded *if necessary*
  //     round_at(xyz.abcd,-1) |-> xy.zabc |-> x|y|, where |y| is rounded *if necessary*
}


double round_at(const double& in_value, int decimal_point = 0)
{
  return std::round(in_value * std::pow(10.,decimal_point)) * std::pow (10., -decimal_point);//
  //this takes a double: xyz.abcd -> shifts the decimal_point (if positive it makes the number larger)
  // so: round_at(xyz.abcd)    |-> xy|z|           , where |z| is rounded *if necessary*
  //     round_at(xyz.abcd,-1) |-> xy.zabc |-> x|y|, where |y| is rounded *if necessary*
}


long double round_at(const long double& in_value, int decimal_point = 0)
{
  return std::round(in_value * std::pow(10.,decimal_point)) * std::pow (10., -decimal_point);//
  //this takes a double: xyz.abcd -> shifts the decimal_point (if positive it makes the number larger)
  // so: round_at(xyz.abcd)    |-> xy|z|           , where |z| is rounded *if necessary*
  //     round_at(xyz.abcd,-1) |-> xy.zabc |-> x|y|, where |y| is rounded *if necessary*
}


//full specialization
template <>
std::string to_fixed_string<double>(const double & in_type, const int in_precision)
{
  if (std::is_floating_point<double>::value && boost::math::isinf(in_type))
  {
    std::string in_function = __PRETTY_FUNCTION__;
    throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);//double expand this macro will make this a c-string
  }
  std::stringstream to_string;
  to_string.setf(std::ios::fixed);
  to_string.setf(std::ios::showpoint);
  to_string.precision(in_precision);
  if (in_precision <= 0)
  {
    to_string << std::noshowpoint;
    to_string.precision(0);
    double rounded = round_at(in_type, in_precision);
    to_string << rounded;
    return to_string.str();
  }
  to_string << in_type;
	return to_string.str();
}

int maximum_exponent(const double value_1, const double value_2)
{
  return std::max<int>(exponent<double>(value_1), exponent<double>(value_2));
}

int minimum_exponent(const double value_1, const double value_2)
{
  return std::min<int>(exponent<double>(value_1), exponent<double>(value_2));
}

std::string
to_string_max_exponent(const double value_1, const double value_2)
{
  return boost::lexical_cast<std::string>(maximum_exponent(value_1,value_2));
}

std::string
to_string_min_exponent(const double value_1, const double value_2)
{
  return boost::lexical_cast<std::string>(minimum_exponent(value_1,value_2));
}



