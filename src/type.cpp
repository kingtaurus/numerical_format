
#include "type.hpp"
#ifdef __GNUG__

#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string to_string_type(const char* name)
{
  int status = -999;
  std::unique_ptr<char, void(*)(void*)> res(abi::__cxa_demangle(name, nullptr, nullptr, &status),
    std::free);//the resource allocated by __cxa_demangle has to be freed;

  return (status==0) ? res.get() : name;
}

#else
std::string to_string_type(const char * name)
{
  return name;
}

//
//http://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
//

#endif


