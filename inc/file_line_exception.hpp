#ifndef FILE_LINE_EXCEPTION_HPP
#define FILE_LINE_EXCEPTION_HPP

#include <sstream>
#include <stdexcept>

#include "inc/macro_definitions.hpp"

class file_line_runtime_error : 
  public std::runtime_error
{
private:
  std::string msg;
public:
  file_line_runtime_error(const std::string& arg, const char * file, size_t line) :
    std::runtime_error(arg)
  {
    std::ostringstream o;
    o << file << ": " << line << "; " << arg;
    msg = o.str();
  }
  ~file_line_runtime_error() throw()
  {
  }
  const char *what() const throw()
  {
    return msg.c_str();
  }
};

#define throw_line(arg) throw file_line_runtime_error(arg, __FILE__, __LINE__);

#endif


