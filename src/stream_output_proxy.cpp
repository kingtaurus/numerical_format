#include "stream_output_proxy.hpp"
#include "error_helper_def.hpp"
#include "symmetric_error.hpp"
#include <boost/lexical_cast.hpp>

//std::string to_string(const error_type x)
//{
//  return std::string("");
//}

//std::string to_latex_string(const error_type x)
//{
//  return std::string("");
//}


std::string
to_string_symmetric(const double in_value, const double in_error)
{
  int max_exponent   = maximum_exponent(in_value,in_error);

  std::string error_string = symmetric_error::to_string_error(in_value, in_error);
  std::string value_string = symmetric_error::to_string_value(in_value, in_error);

  if (max_exponent == 0)
  {
    return "(" + value_string + "+-" + error_string + ")";
  }
	return "(" + value_string + "+-" + error_string + ")E" + boost::lexical_cast<std::string>(max_exponent);
}

std::string
to_latex_string_symmetric(const double in_value, const double in_error)
{
  int max_exponent   = maximum_exponent(in_value,in_error);

  std::string error_string = symmetric_error::to_string_error(in_value, in_error);
  std::string value_string = symmetric_error::to_string_value(in_value, in_error);
  //std::replace( s.begin(), s.end(), ' ', '~');
  //replace all spaces with ~
  if (max_exponent == 0)
  {
	  return "\\left(" + value_string + "\\pm" + error_string + "\\right)";
  }
	return "\\left(" + value_string + "\\pm" + error_string + "\\right)E " + boost::lexical_cast<std::string>(max_exponent);
}

std::string
to_string_symmetric(const error_type& in_error)
{
  return to_string_symmetric(in_error.first, in_error.second);
}

std::string
to_latex_string_symmetric(const error_type& in_error)
{
  return to_latex_string_symmetric(in_error.first, in_error.second);
}


