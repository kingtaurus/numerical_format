#ifndef TWODIGITS_ERROR_HPP
#define TWODIGITS_ERROR_HPP

#include <string>
#include <tuple>
#include <vector>

#include "error_helper_def.hpp"

namespace twodigits_error
{
  std::string to_string_value(const double, const double);
  std::string to_string_error(const double, const double);

  int get_exponent(const double in_value, const double in_error);
  int get_max_exponent(std::vector<double>);
  int get_min_exponent(std::vector<double>);

  std::string to_string_value_fixed(const double, const double);
  std::string to_string_error_fixed(const double, const double);
}

#endif
