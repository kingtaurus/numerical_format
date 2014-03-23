
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

    //exponent is the same (no rounding worry)
    if (exponent_value == exponent_error)
    {
      return to_fixed_string(decimal_representation<double>(in_value), 1);//then just need to tag an error on the end;
    }

    //if they are different (need to change the precision on the larger one)
    // then exponent_value can drop by 1 (more precision means less likely
    // to round up);
    if (exponent_value > exponent_error)
    {
      exponent_value = exponent<double>(in_value,std::abs(exponent_error) + 1);
    }
    else if (exponent_value < exponent_error)
    {
      exponent_error = exponent<double>(in_error,std::abs(exponent_value) + 1);
    }

   	int min_exponent = std::min<int>(exponent_value, exponent_error);
    int max_exponent = std::max<int>(exponent_value, exponent_error);
	
    int precision = max_exponent - min_exponent + 1;

	  double scale_value = pow(10., std::min(0, exponent_value - max_exponent));

    //because precision may be larger than 1, can't call
    //decimal_representation<double>(in_value, precision)
    //[i.e. decimal_rep(in_value,precision) * scale_value, might be rounded by to_fixed_string]
    if (exponent_value < exponent_error)
    {
      return to_fixed_string(two_digits_double(in_value)*scale_value, precision);
    }
    //
    return to_fixed_string(decimal_representation<double>(in_value,precision)*scale_value,precision);
  }

  std::string to_string_error(const double in_value, const double in_error)
  {
 	  int exponent_value = exponent<double>(in_value);
	  int exponent_error = exponent<double>(in_error);

    //exponent is the same (no rounding worry)
    if (exponent_value == exponent_error)
    {
      return to_fixed_string(decimal_representation<double>(in_error),1);
    }

    //if they are different (need to change the precision on the larger one)
    // then exponent_value can drop by 1 (more precision means less likely
    // to round up);
    if (exponent_value > exponent_error)
    {
      //so if exponent_value is larger
      exponent_value = exponent<double>(in_value,1+std::abs(exponent_error));
    }
    else if (exponent_value < exponent_error)
    {
      exponent_error = exponent<double>(in_error,1+std::abs(exponent_value));
    }

   	int min_exponent = std::min<int>(exponent_value, exponent_error);
    int max_exponent = std::max<int>(exponent_value, exponent_error);
	
	  int precision = max_exponent - min_exponent + 1;

	  double scale_error = pow(10., std::min(0, exponent_error - max_exponent));
    if (exponent_error < exponent_value)
    {
      return to_fixed_string(two_digits_double(in_error)*scale_error, precision);
    }
    return to_fixed_string(decimal_representation<double>(in_error,precision)*scale_error,precision);
  }

  int get_exponent(const double in_value, const double in_error)
  {
    int exponent_value = exponent<double>(in_value);
	  int exponent_error = exponent<double>(in_error);
    //exponent is the same
    if(exponent_value == exponent_error)
    {
      return exponent_value;
    }
    if (exponent_value > exponent_error)
    {
      //so if exponent_value is larger
      exponent_value = exponent<double>(in_value,1 + std::abs(exponent_error));
    }
    else if (exponent_value < exponent_error)
    {
      exponent_error = exponent<double>(in_error,1 + std::abs(exponent_value));
    }
    return std::max<int>(exponent_value,exponent_error);
  }

  int get_min_exponent(std::vector<double> in_vector)
  {
    if (in_vector.empty())
    {
      std::string in_function = __PRETTY_FUNCTION__;
      throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);
    }

    int min_exponent = exponent<double>(in_vector[0]);

    for (auto& element : in_vector)
    {
      min_exponent = std::min(min_exponent, exponent<double>(element));
    }

    return min_exponent;
  }

  int get_max_exponent(std::vector<double> in_vector)
  {
    if (in_vector.empty())
    {
      std::string in_function = __PRETTY_FUNCTION__;
      throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);
    }
    int min_exponent = get_min_exponent(in_vector);
    //(find minimum exponent; then find maximum exponent)
    int max_exponent = min_exponent;
    for (auto & element : in_vector)
    {
      max_exponent = std::max(max_exponent, exponent<double>(element,1+std::abs(min_exponent)));
    }

    return max_exponent;
  }

  std::string
  to_string_value_fixed(const double in_value, const double in_error)
  {
   	int min_exponent = minimum_exponent(in_value,in_error);
	  int precision = std::abs(min_exponent) + 1;
    return to_fixed_string(in_value, precision);
  }

  std::string
  to_string_error_fixed(const double in_value, const double in_error)
  {
   	int min_exponent = minimum_exponent(in_value,in_error);
	  int precision = std::abs(min_exponent) + 1;
    return to_fixed_string(in_error, precision);
  }


  //Name?
  std::tuple<std::string, std::vector<std::string>, int>
  to_tuple_multi_errors(const double in_value, const std::vector<double>& in_vector_errors)
  {

    if (in_vector_errors.empty())
    {
      std::string in_function = __PRETTY_FUNCTION__;
      throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);
    }

    std::vector<double> all_values = in_vector_errors;
    all_values.push_back(in_value);

    int current_min_expo = get_min_exponent(all_values);
    int current_max_expo = get_max_exponent(all_values);

    //create a dummy value to call against;
    double dummy_value = 1.1 * pow(10., current_min_expo);
    std::string out_string = to_string_value(in_value, dummy_value);

    std::vector<std::string> error_string;
    for ( auto & error : in_vector_errors )
    {
      std::string out_error_string = to_string_value(error, dummy_value);
      error_string.push_back(out_error_string);
    }
    return std::tuple<std::string, std::vector<std::string>, int>(out_string, error_string, current_max_expo);
  }

  //Probably should name this better
  std::string
  value_to_string_multiple_errors(const double x, const std::vector<double>& vector_of_errors)
  {
    std::tuple<std::string, std::vector<std::string>, int> cont = to_tuple_multi_errors(x,vector_of_errors);
    std::string out_str = std::get<0>(cont);
    if (int expo = std::get<2>(cont))
    {
      out_str += "E" + boost::lexical_cast<std::string>(expo);
    }
    return out_str;
  }

  //Probably should name this better
  std::vector<std::string>
  to_string_multiple_errors_into_vector(const double x, const std::vector<double>& vector_of_errors)
  {
    std::tuple<std::string, std::vector<std::string>, int> cont = to_tuple_multi_errors(x,vector_of_errors);

    std::vector<std::string>& error_strings = std::get<1>(cont);
    if (int expo = std::get<2>(cont))
    {
      for( auto& error : error_strings)
      {
        error += "E" + boost::lexical_cast<std::string>(expo);
      }
    }
    return error_strings;
  }


  //THIS might be moved to a seperate translation unit
  std::pair<std::string,std::string>
  to_string_no_exponent(const double value_1, const double value_2)
  {
    int min_expo = minimum_exponent(value_1, value_2);
    int prec     = 1;
    if (min_expo < 0)
    {
      prec = std::abs(min_expo) + 1;
    }
    int width_value_1 = int(to_fixed_string(value_1, prec).size());
    int width_value_2 = int(to_fixed_string(value_2, prec).size());

    int max_width     = std::max(width_value_1,width_value_2);

    std::stringstream value_1_string_stream;
    std::stringstream value_2_string_stream;

    //right aligned, with fixed width (good for a column)
    //surprised by this: std::setw(int) why?
    value_1_string_stream << std::setw(max_width) << std::setprecision(prec) << std::setiosflags(std::ios::right | std::ios::fixed | std::ios::showpoint);
	    value_1_string_stream <<  value_1;

    value_2_string_stream << std::setw(max_width) << std::setprecision(prec) << std::setiosflags( std::ios::right |std::ios::fixed | std::ios::showpoint);
      value_2_string_stream << value_2;

    return std::make_pair(value_1_string_stream.str(), value_2_string_stream.str());
  }

  //probably should rename this
  //behaviour is fixed point (so ... maybe rework this)
  std::vector<std::string>
  to_string_no_exponent(const std::vector<double>& vec)
  {
    if (vec.empty())
    {
      std::string in_function = __PRETTY_FUNCTION__;
      throw std::runtime_error("exception in function " + in_function + "in " __FILE__ " " STRING__LINE__);
    }

    std::vector<int> exponents;
    //std::function<int(double)> a_func = std::bind(exponent<double>,std::placeholders::_1);
    std::transform(vec.begin(), vec.end(),
                   std::back_inserter(exponents),
                   [](double in_value)
                   {
                     return exponent<double>(in_value);
                   });

    int min_expo = *std::min_element(exponents.begin(), exponents.end());
    int prec = 1;
    if (min_expo < 0)
    {
      prec = std::abs(min_expo) + 1;
    }

    int max_width = 0;
    for (auto & in : vec)
    {
      max_width = std::max(max_width, int(to_fixed_string(in,prec).size())) ;
    }

    std::vector<std::string> out_vector = {};
    for(size_t i = 0; i < vec.size(); ++i )
    {
      std::stringstream value_string_stream;
      value_string_stream << std::setw(max_width)
                          << std::setprecision(2)
                          << std::setiosflags(std::ios::right | std::ios::fixed | std::ios::showpoint)
                          << vec[i];
      out_vector.push_back( value_string_stream.str() );
    }
    return out_vector;
  }


  std::vector<std::string>
  to_string_no_exponent(const double value_1,
                        const double value_2,
                        const double value_3)
  {
    //Original VERSION:
    //  int min_expo_12 = minimum_exponent(value_1, value_2);
    //  int min_expo_23 = minimum_exponent(value_2, value_3);
    //  int min_expo = std::min(min_expo_12, min_expo_23);
    //  int prec = 2;
    //  if (min_expo < 0)
    //  {
    //    prec = std::abs(min_expo) + 1;
    //  }
    //  size_t width_value_1 = to_fixed_string<double>(value_1, prec).size();
    //  size_t width_value_2 = to_fixed_string<double>(value_2, prec).size();
    //  size_t width_value_3 = to_fixed_string<double>(value_3, prec).size();
    //  size_t max_width     = std::max({width_value_1, width_value_2, width_value_3});
    //  //C++11 version
    //  //C++03
    //  //size_t max_width   = std::max(std::max(width_value_1, width_value_2), width_value_3);
    //  std::stringstream value_string_stream;
    //  std::vector<std::string> out_vector;
    //  value_string_stream << std::setw(max_width)  << std::setiosflags(std::ios::right | std::ios::fixed | std::ios::showpoint) << value_1;
    //  out_vector.push_back(value_string_stream.str());
    //  value_string_stream.str(std::string());
    //  value_string_stream << std::setw(max_width) << std::setiosflags(std::ios::right | std::ios::fixed | std::ios::showpoint) << value_2;
    //  out_vector.push_back(value_string_stream.str());
    //  value_string_stream.str(std::string());
    //  value_string_stream << std::setw(max_width) << std::setiosflags(std::ios::right | std::ios::fixed | std::ios::showpoint) << value_3;
    //  out_vector.push_back(value_string_stream.str());
    //  value_string_stream.str(std::string());
    //  return out_vector;
    return to_string_no_exponent({value_1,value_2,value_3});
  }

  std::vector<std::string>
  to_string_no_exponent(const double value_1,
                        const double value_2,
                        const double value_3,
                        const double value_4)
  {
    return to_string_no_exponent({value_1,value_2,value_3,value_4});
  }


}

