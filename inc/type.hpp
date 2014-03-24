#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <typeinfo>

//forward declaration
std::string get_type(const char* name);

template <typename T>
std::string type(const T& t)
{
  return get_type(typeid(t).name());
}


#endif
