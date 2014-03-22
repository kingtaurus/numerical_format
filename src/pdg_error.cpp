#include "pdg_error.hpp"

namespace pdg_error
{
  template <typename T>
  inline double three_digit_decimal_rep(const T& in_decimal)
  {
	  std::string a_string = to_sci_string<T>(in_decimal,2);
	  a_string.erase(a_string.find_first_of("Ee"), std::string::npos);
	  return boost::lexical_cast<double>(a_string);
  }

  template <typename T>
  int pdg_exponent(const T& in_value, const T& in_error)
  {
    int value_exponent = exponent<double>(in_value);
    int error_exponent = exponent<double>(in_error);

    if (three_digit_decimal_rep(in_error) >= 9.50)
    {
      error_exponent += 1;//rounding up
    }
    int max_exponent = std::max<int>(value_exponent, error_exponent);

    return max_exponent;
  }

  template <typename T>
  std::string to_string_value(const T& in_value, const T& in_error)
  {
    double three_digit_error = three_digit_decimal_rep(in_error);
    int error_exponent = exponent<double>(in_error);
    int shift_precision = 1;

    if (three_digit_error > 0.999 && three_digit_error < 3.55)
    {
      shift_precision = 1;
    }
    else if (three_digit_error >= 3.55 && three_digit_error < 9.50)
    {
      shift_precision = 0;
    }
    else if (three_digit_error >= 9.50)
    {
      shift_precision = 1;
      error_exponent += 1;//rounding up
    }
    double value   = round_at(in_value, -error_exponent + shift_precision);
    int    exponent_shift = pdg_exponent(in_value, in_error);
    return to_fixed_string<double>(value*pow(10,-exponent_shift), 
                                   exponent_shift - error_exponent + shift_precision);
  }

  template <typename T>
  std::string to_string_error(const T& in_value, const T& in_error)
  {
    double three_digit_error = three_digit_decimal_rep(in_error);
    int error_exponent = exponent<double>(in_error);
    int shift_precision = 1;

    if (three_digit_error > 0.999 && three_digit_error < 3.55)
    {
      shift_precision = 1;
    }
    else if (three_digit_error >= 3.55 && three_digit_error < 9.50)
    {
      shift_precision = 0;
    }
    else if (three_digit_error >= 9.50)
    {
      shift_precision = 1;
      three_digit_error = 1.00;
      error_exponent += 1;//rounding up
    }
    //pdg_exponent (is the value that both have to be scaled by);
    //so
    //5.7885E(x)-> 5.7885 when shifting by 10^(-x)
    //so if you have a decimal expansion (this is equivalent to being shifted by)
    //-exponent
    //so we want 
    //5.7885 -> 5.7885E(x) and then by pdg_exponent
      
    double rounded        = round_at(three_digit_error, shift_precision);
    int    exponent_shift = pdg_exponent(in_value, in_error);
    return to_fixed_string<double>(rounded * pow(10.,error_exponent - exponent_shift), 
                                   exponent_shift - error_exponent + shift_precision);
  }

  template <typename T>
  std::string to_string_value_fixed(const T& in_value, const T& in_error)
  {
    double three_digit_error = three_digit_decimal_rep(in_error);
    int error_exponent = exponent<double>(in_error);
    int shift_precision = 1;

    if (three_digit_error > 0.9999 && three_digit_error < 3.55)
    {
      shift_precision = 1;
    }
    else if (three_digit_error >= 3.55 && three_digit_error < 9.50)
    {
      shift_precision = 0;
    }
    else if (three_digit_error >= 9.50)
    {
      shift_precision = 1;
      error_exponent += 1;//rounding up
    }

    double value   = round_at(in_value, -error_exponent + shift_precision);

    if( error_exponent > 0)
    {
      return to_fixed_string<double>(value, 0);
    }
    return to_fixed_string<double>(value, std::abs(error_exponent) + shift_precision);
  }

  template <typename T>
  std::string to_string_error_fixed(const T& in_value, //const T& in_value __attribute__((unused)),
                                    const T& in_error)
  {
    UNUSED(in_value);
    double three_digit_error = three_digit_decimal_rep(in_error);
    int error_exponent = exponent<double>(in_error);
    int shift_precision = 1;

    if (three_digit_error > 0.999 && three_digit_error < 3.55)
    {
      shift_precision = 1;
    }
    else if (three_digit_error >= 3.55 && three_digit_error < 9.50)
    {
      shift_precision = 0;
    }
    else if (three_digit_error >= 9.50)
    {
      shift_precision = 1;
      three_digit_error = 1.000;
      error_exponent += 1;//rounding up
    }

    double output = round_at(three_digit_error, shift_precision) * pow(10., error_exponent);
    if (error_exponent > 0)
    {
      return to_fixed_string<double>(output, 0);
    }
    return to_fixed_string<double>(output, std::abs(error_exponent) + shift_precision);
  }
}

