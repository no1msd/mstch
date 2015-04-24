# mstch - {{mustache}} templates in C++11 

![mstch logo](http://i.imgur.com/GM8V88a.png)

mstch is a complete implementation of [{{mustache}}](http://mustache.github.io/) templates using modern C++.

[![Build Status](https://travis-ci.org/no1msd/mstch.svg?branch=master)](https://travis-ci.org/no1msd/mstch)

## Supported features

mstch supports the complete feature set described in the `mustache(5)` [manpage](http://mustache.github.com/mustache.5.html):

 - JSON-like data structure using [Boost.Variant](http://www.boost.org/doc/libs/1_57_0/doc/html/variant.html)
 - variables, sections, inverted sections
 - partials
 - changing the delimiter
 - C++11 lambdas
 - C++ objects as view models

## Basic usage

```c++
#include <iostream>
#include <mstch/mstch.hpp>

int main() {
  std::string view{"{{#names}}Hi {{name}}!\n{{/names}}"};
  mstch::map context{
    {"names", mstch::array{
      mstch::map{{"name", std::string{"Chris"}}},
      mstch::map{{"name", std::string{"Mark"}}},
      mstch::map{{"name", std::string{"Scott"}}},
    }}
  };
  
  std::cout << mstch::render(view, context) << std::endl;
  
  return 0;
}

```

The output of this example will be:

```
Hi Chris!
Hi Mark!
Hi Scott!
```

## Requirements

 - A C++ compiler with decent C++11 support. Currently only tested with GCC 4.9.
 - Boost 1.54
 - CMake for building

## Installing

From the root of the source tree:

```bash
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
 $ make install
```

### Running the unit tests

```bash
 $ mkdir build
 $ cd build
 $ cmake -DWITH_UNIT_TESTS=ON ..
 $ make
 $ make test
```

## Advanced usage

TODO