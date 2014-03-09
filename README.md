numerical_format
================
C++ Header Library Designed for formatting number +/- error;

Dependencies
------------
* C++11 (either clang++ or g++)
* Boost (test, math, system, lexical_cast, multiprecision)
* cmake
* ccache (Optional - only if you want to build using it)
* libmpfr-dev

A stable version of `clang++` is available [llvm-apt](http://llvm.org/apt);


Building
--------
To build the library,

`mkdir build`

`cd build`

Then run of the following commands:
  - `CC="gcc" CXX="g++" cmake ../ -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=None`
  - `CC="ccache gcc" CXX="ccache g++" cmake ../ -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=None`
  - `CC="ccache clang" CXX="ccache clang++" cmake ../ -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=None`

`None` **can be replaced with one the following:** `Debug, Release, RelWithDebInfo, MinSizeRel, Coverage;`

`make all && make test` **will build and run the unit tests;**

Code Coverage
-------------
#### Requires 
* lcov
* gcov
* genhtml
* gcovr

#### Generate a coverage report:
`make all && make test && make all_coverage`    **Use None, Debug, or Coverage build modes;**

`<browser> results/index.html` **view the coverage report;**




<!--Boost-specific details:-->
<!--    ./bootstrap --prefix=$HOME/boost-->
<!--    ./b2 clean-->
<!--    ./b2 install toolset=clang cxxflags="-stdlib=libc++" linkflags="-stdlib=libc++"-->
<!--Using CMake to compile Armatus:-->
<!--    cmake -DCMAKE_CXX_COMPILER=clang++ -DBOOST_ROOT=$HOME/boost -DBoost_NO_SYSTEM_PATHS=true ..-->
<!--    make-->
<!--Make sure you substitute `$HOME/boost` with the installation path you desire.-->

<!--The [Tutorial](https://github.com/Amanieu/asyncplusplus/wiki/Tutorial) provides a step-by-step guide to all the features of Async++.-->

About
-----

### PDG rounding


The basic rule:

  a. If the three highest order digits of the error lie between 100 and 354
  round to two significant digits.
  
  b. If the three highest order digits of the error lie between 355 and 949
  round to one significant digit.
  
  c.If the three highest order digits of the error lie between 950 and 999
  round up to 1000 and keep two significant digits.

In all cases the central value is given with a precision that matches that of
the error.

####For example,
####**|central value|   <   |error|**
  - `0.827 ± 0.119`  &rarr; `0.83 ± 0.12`
  - `0.827 ± 0.367`  &rarr; `0.8  ± 0.4`
  - `1.827 ± 0.967`  &rarr; `1.8  ± 1.0`

####**|central value|   <   |error|**
  - `0.0119 ± 0.122` &rarr; `0.01 ± 0.12`
  - `0.0119 ± 0.827` &rarr; `0.0  ± 0.8`
  - `0.0367 ± 0.977` &rarr; `0.0  ± 1.0`

Rounding is not performed if a result comes from a single measurement (without
any averaging). In that case, the number of digits published in the original
paper is kept (unless *we* **[PDG]** feel it inappropriate).


### Symmetric Rounding

The basic rule:
  - **|central value|** > **|error|**; then the precision on the **error** is two significant
digits, the precision on the central value matches that of the error.
  - **|central value|** < **|error|**; then the precision on the **central value** is two
significant digits, the precision on the error matches that of the central
value.

The precision is two significant digits on the **lesser significant value** and the
other value has precision that matches that of the **lesser significant value**.

For example,
  - `0.827 ± 0.119`  &rarr;  `0.83  ± 0.12`
  - `0.827 ± 0.367`  &rarr;  `0.83  ± 0.37`
  - `0.827 ± 0.0119` &rarr;  `0.827 ± 0.012`
  - `0.827 ± 0.0367` &rarr;  `0.827 ± 0.037`
  - `0.0119 ± 0.827` &rarr;  `0.012 ± 0.827`
  - `0.0367 ± 0.827` &rarr;  `0.037 ± 0.827`

### Terminal Aligning

The basic rule:
If given *n* (*n &ge; 1*) decimal values; say *x*&#x2081;,...,*x*&#x2099; these values can be
decimal point aligned. 
#### NOTES:
- currently using precision of 2 when (&#x2200; **l** | *x*&#x2097; > 1.0);
- precision is fixed to be 1 more than the *least signficant* (&#x2203; **l** | *x*&#x2097; < 1.0 )
 - in other words if one of the value is in the range (-1,1);

For example,
```
1459.210
   2.110
  -0.020
```
or
```
0.0125
0.0022
0.0059
```
### Latex Aligning
Uses Terminal Aligning, but then replaces ' ' with '~'; then encapsulates the
entire string within ```\ensuremath{}```.

### TODO LIST
  - Can use `+/-`, `±`
  - Better Example
  - Latex Aligning
  - Terminal Aligning
  - Changing locale breaks tests (because imbuing a gloabl locale changes number formatting)
  - Added an executable: `format_error --pdg central_value error`; `format_error --pdg --latex central_value error`; `format_error --simple central_value error_1 error_2`; `format_error --utf ...`; `format_error --latex --name=...`
  - Add additional tests;
  - Need to fix a problem related to not having an /etc/ld.so.conf.d config file (and then re-running ldconfig)
  - static libraries work; adding to the link command `/usr/lib/numeric_error_format/libpdg.a`
  
Example Usage
-------------
If you install the package using the DEB. To use the code you'd do something like:

```C++
#include "numeric_error_format/symmetric_error.hpp"

to_fixed_string<double>(x.yzabc,3);//[std::string] x.yza
```

`g++ -std=c++11 <your_code>.cpp -L/usr/lib/numeric_error_format -lpdg -lsymmetric`**Doesn't work yet**
`g++ -std=c++11 <your_code>.cpp /usr/lib/numeric_error_format/libsymmetric.a` ** DOES WORK**

