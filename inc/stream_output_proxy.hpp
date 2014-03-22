#ifndef STREAM_OUTPUT_PROXY_HPP
#define STREAM_OUTPUT_PROXY_HPP

#include <iostream>
#include <tuple>
#include <utility>
#include <cmath>
#include <string>

#include "macro_definitions.hpp"

std::string to_string_symmetric_error( std::pair<double,double>);
std::string to_string_pdg_error( std::pair<double,double>);

std::string to_latex_string_symmetric_error(std::pair<double,double>);
std::string to_latex_string_pdg_error(std::pair<double,double>);


struct error_output_creater       {};// eoc;
struct latex_error_output_creater {};// leoc;
struct latex_ensuremath_creater   {};// emoc;

static error_output_creater       eoc;//just need one creater
static latex_error_output_creater leoc;
static latex_ensuremath_creater   emoc;

struct error_output_proxy;

//defaults to symmetric
struct error_output_proxy
{
  explicit error_output_proxy(std::ostream & os) : m_os(os) {}
  friend std::ostream& operator<<(error_output_proxy const& q,
                                  std::pair<double,double> right_hand)
  {
    return q.m_os << to_string_symmetric_error(right_hand);
  }

  template <typename rhs>
  friend std::ostream & operator<<(error_output_proxy const& q,
                                   rhs const& right_hand)
	{
	  return q.m_os << right_hand;
	}
private:
  std::ostream & m_os;
};

error_output_proxy operator<<(std::ostream & in_os, error_output_creater in_eoc)
{
  UNUSED(in_eoc);
  return error_output_proxy(in_os);
}
//called as (example):
//std::cout << numerical_output::eoc << [error_type] a;

struct latex_ensuremath_proxy
{
  explicit latex_ensuremath_proxy(std::ostream& os) : m_os(os) {}

  template <typename rhs>
  friend std::ostream& operator<<(latex_ensuremath_proxy const& q,
                                  rhs const& right_hand)
  {
    return q.m_os << "\\ensuremath{" << right_hand << "}";
  }

  private:
    std::ostream & m_os;
};

latex_ensuremath_proxy operator<<(std::ostream& in_os, latex_ensuremath_creater in_emoc)
{
  UNUSED(in_emoc);
  return latex_ensuremath_proxy(in_os);
}
//called as:
//std::cout << numerical_output::emoc << a;

struct latex_error_output_proxy
{
	explicit latex_error_output_proxy(std::ostream & os) : m_os(os) {}

	friend std::ostream & operator<<(latex_error_output_proxy const& q,
	                                 std::pair<double,double> right_hand)
	{
    return q.m_os << to_latex_string_symmetric_error(right_hand);
	}

  friend std::ostream& operator<<(latex_error_output_proxy const& q,
                                  std::tuple<std::string,std::pair<double,double>> const& right_hand)
  {
    //\def{testdef}   {\ensuremath{(1.00\pm0.50)E-1}}
    return q.m_os << "\\def\\"
                  << std::get<0>(right_hand) << "{" << emoc
                  << to_latex_string_symmetric_error(std::get<1>(right_hand))
                  << "}";
  }

	template <typename rhs>
	friend std::ostream & operator<<(latex_error_output_proxy const& q,
	                                 rhs const& right_hand)
	{
		return q.m_os << right_hand;
	}
		
private:
	std::ostream & m_os;
};

latex_error_output_proxy operator<<(std::ostream & in_os, latex_error_output_creater in_leoc)
{
  UNUSED(in_leoc);
  return latex_error_output_proxy(in_os);
}
//called as:
//std::cout << numerical_output::leoc << [error_type] a;


#endif

