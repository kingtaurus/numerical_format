#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "twodigits_error.hpp"

namespace twodigits_error
{
  std::string to_string_value(const double in_value, const double in_error)
  {
    //int exponent_error = exponent<double>(in_error);
    return std::string("");
  }
  
  std::string to_string_error(const double in_value, const double in_error)
  {
    std::string a_string = to_sci_string(in_error,1);
    a_string.erase(a_string.find_first_of("Ee"), std::string::npos);
    return boost::lexical_cast<double>(a_string);
  }
}
