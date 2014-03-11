#ifndef SYMMETRIC_ERROR_HPP
#define SYMMETRIC_ERROR_HPP

#include <string>
#include <tuple>
#include <vector>

#include "error_helper_def.hpp"

namespace symmetric_error
{
  std::string to_string_value(const double, const double);
  std::string to_string_error(const double, const double);

  std::string to_string_value_fixed(const double, const double);
  std::string to_string_error_fixed(const double, const double);

  std::tuple<std::string, std::vector<std::string>, int>
  to_tuple_multi_errors(const double x, const std::vector<double>& in_vector_errors);

  std::string
  value_to_string_multiple_errors(const double x, const std::vector<double>& vector_of_errors);

  std::vector<std::string>
  to_string_multiple_errors_into_vector(const double x, const std::vector<double>& vector_of_errors);

  std::pair<std::string,std::string>
  to_string_no_exponent(const double value_1, const double value_2);

  std::vector<std::string>
  to_string_no_exponent(const std::vector<double>& vec);

  std::vector<std::string>
  to_string_no_exponent(const double value_1,
                        const double value_2,
                        const double value_3);

  std::vector<std::string>
  to_string_no_exponent(const double value_1,
                        const double value_2,
                        const double value_3,
                        const double value_4);

}

#endif
