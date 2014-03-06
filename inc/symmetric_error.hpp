#ifndef SYMMETRIC_ERROR_HPP
#define SYMMETRIC_ERROR_HPP

#include <string>
#include "error_helper_def.hpp"

namespace symmetric_error
{
  std::string to_string_value(const double, const double);
  std::string to_string_error(const double, const double);

  std::string to_string_value_fixed(const double, const double);
  std::string to_string_error_fixed(const double, const double);
}

#endif
