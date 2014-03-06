
#include <sstream>

#include <algorithm>
#include <stdexcept>

#include "symmetric_error.hpp"

namespace symmetric_error
{
  std::string to_string_value(const double in_value, const double in_error)
  {
    int exponent_value = exponent<double>(in_value);
    int exponent_error = exponent<double>(in_error);

   	int min_exponent = std::min<int>(exponent_value, exponent_error);
    int max_exponent = std::max<int>(exponent_value, exponent_error);
	
    int precision = max_exponent - min_exponent + 1;
	  double scale_value = pow(10., std::min(0, exponent_value - max_exponent));

	  std::stringstream value_string_stream;
    value_string_stream.precision(precision);
	  value_string_stream.setf( std::ios::fixed | std::ios::showpoint );
	  value_string_stream << (decimal_representation<double>(in_value) * scale_value);
    return value_string_stream.str();
  }

  std::string
  to_string_error(const double value, const double error)
  {
	  int exponent_value = exponent<double>(value);
	  int exponent_error = exponent<double>(error);

	  int min_exponent = std::min<int>(exponent_value, exponent_error);
	  int max_exponent = std::max<int>(exponent_value, exponent_error);
	
	  int precision = max_exponent - min_exponent + 1;

	  double scale_error = pow(10., std::min(0, exponent_error - max_exponent));

    return to_fixed_string(decimal_representation<double>(error) * scale_error, precision);
//	  std::stringstream error_string_stream;
//	  error_string_stream << std::setprecision(precision) << std::setiosflags(std::ios::fixed | std::ios::showpoint);
//	  error_string_stream << (decimal_representation<double>(error) * scale_error);		

//	  return error_string_stream.str();
  }

  std::string 
  to_string_value_fixed(const double in_value, const double in_error)
  {
   	int min_exponent = minimum_exponent(in_value,in_error);
	  int precision = std::abs(min_exponent) + 1;
    return to_fixed_string(in_value, precision);
//	  std::stringstream value_string_stream;
//    value_string_stream.precision(precision);
//	  value_string_stream.setf( std::ios::fixed | std::ios::showpoint );
//	  value_string_stream << in_value;
//    return value_string_stream.str();
  }

  std::string
  to_string_error_fixed(const double in_value, const double in_error)
  {
   	int min_exponent = minimum_exponent(in_value,in_error);
	  int precision = std::abs(min_exponent) + 1;
    return to_fixed_string(in_error, precision);
//	  std::stringstream error_string_stream;
//	  error_string_stream << std::setprecision(precision) << std::setiosflags(std::ios::fixed | std::ios::showpoint);
//	  error_string_stream << (decimal_representation<double>(error) * scale_error);		

//	  return error_string_stream.str();
  }

  
}

