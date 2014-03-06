#ifndef MACRO_DEFINITIONS_HPP
#define MACRO_DEFINITIONS_HPP

#ifndef UNUSED
#define UNUSED(expr) do { (void)(expr); } while (0)
#endif

#define STRING_LINE_NUMBER(x) # x
#define STRING_LINE_NUMBER_(x)  STRING_LINE_NUMBER(x)
#define STRING__LINE__ STRING_LINE_NUMBER_(__LINE__)
//use STRING__LINE__ to get a 'stringified' expansion of __LINE__
// (1) Macro arguments are completely macro-expaned before they are substituted
// into a macro body, __UNLESS__
//   (a) they are stringified; or
//   (b) pasted with other tokens.
//
// After substitution, the entire macro body including the substituted arguments
// is scanned again for macros to be expaned. The result is that the arguements
// are scanned twice to expand macro calls within them.
//
// STRING_LINE_NUMBER(x) # x        |-> converts x to a c-style string
// STRING_LINE_NUMBER(__LINE__)     |-> becomes "__LINE__" 
//                                  |  [prevents __LINE__ from being expanded]
// STRING_LINE_NUMBER_(x)           |-> STRING_LINE_NUMBER(x)
//                                  |  [x is now expanded]
// STRING_LINE_NUMBER_(__LINE__)    |-> STRING_LINE_NUMBER(L#)
//                                  |-> "L#" (where L# is the line number)
// STRING__LINE__                   |-> STRING_LINE_NUMBER_(__LINE__)
//                                  |-> STRING_LINE_NUMBER(L#)

#endif
