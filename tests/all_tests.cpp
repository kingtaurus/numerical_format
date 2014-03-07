#define BOOST_TEST_MODULE All Unit Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

#include <locale>

#include "type.hpp"

BOOST_AUTO_TEST_CASE (all_tests)
{
  BOOST_MESSAGE("Running all tests;");
  BOOST_MESSAGE("Testing multibyte character rendering ±; \u2780; \u00B1");
//  std::cout << "±"   << std::endl;
//  std::string x = "±";//this character is const char [3]
//  //3 byte character;
//  std::cout << type(x) << std::endl;//std::string
//  std::cout << x << std::endl;//"±"
//  std::cout << "\u2780" << std::endl;
//  std::cout << type("ac") << std::endl;
//  std::cout << "\u00B1"  << std::endl;
//  std::cout << type('c')  << std::endl;
  std::cout << "\u00B1"  << std::endl;
  std::cout << "\u00E9"  << std::endl;
  std::cout << "\u01E9"  << std::endl;

  //http://www.fileformat.info/info/unicode/char/b1/index.htm
  //http://en.wikipedia.org/wiki/ISO_8859-1
  //"\u00xx"; where xx between 00 and 7E is ascii characters
  //"\u00xx"; A0->FF ('extended character set');
  //\u00B1
  //&#xb1;
  //&plusmn;
  //177
}

