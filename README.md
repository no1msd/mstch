# mstch - {{mustache}} templates in C++11 

![mstch logo](http://i.imgur.com/XAdHwUs.png)

mstch is a complete implementation of [{{mustache}}](http://mustache.github.io/) 
templates using modern C++.

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

```html
Hi Chris!
Hi Mark!
Hi Scott!
```

### Data structure

The types in the example above, `mstch::array` and `mstch::map` are  actually 
aliases for standard types:

```c++
using map = std::map<const std::string, node>;
using array = std::vector<node>;
```

`mstch::node` is a `boost::variant` that can hold a `std::string`, `int`, 
`bool`, lambda expression or a `std::shared_ptr` to a `mstch::object` 
(see below), also a map or an array recursively. Essentially it works just like 
a JSON object.

Note that when using a `std::string` as value you must explicitly specify the 
type, since a `const char*` literal like `"foobar"` would be implicitly 
converted to `bool`. Alternatively you can use [C++14 string_literals](http://en.cppreference.com/w/cpp/string/basic_string/operator%22%22s)
if your compiler supports it.

## Advanced usage

### Partials

Partials can be passed in a `std::map` as the third parameter of the 
`mstch::render` function:

```c++
std::string view{"{{#names}}{{> user}}{{/names}}"};
std::string user_view{"<strong>{{name}}\n</strong>"};
mstch::map context{
  {"names", mstch::array{
    mstch::map{{"name", std::string{"Chris"}}},
    mstch::map{{"name", std::string{"Mark"}}},
    mstch::map{{"name", std::string{"Scott"}}},
  }}
};
  
std::cout << mstch::render(view, context, {{"user", user_view}}) << std::endl;
```

Output:

```html
<strong>Chris</strong>
<strong>Mark</strong>
<strong>Scott</strong>
```

### Lambdas

C++11 lambda expressions can be used to add logic to your templates. Like a
`const char*` literal, lambdas can be implicitly converted to `bool`, so they
must be wrapped in a `mstch::lambda` object when used in a `mstch::node`.

The lambda expression passed to `mstch::lambda` returns a `std::string` and 
accepts either no parameters:

```c++
std::string view{"Hello {{lambda}}!"};
mstch::map context{
  {"lambda", mstch::lambda{[]() {
    return std::string{"World"};
  }}}
};

std::cout << mstch::render(view, context) << std::endl;
```

Output:

```html
Hello World!
```

Or it accepts a `const std::string&` and a `mstch::renderer`. The first one is 
passed the unrendered literal block, the second is a `std::function` that can be 
called to render it:

```c++
std::string view{"{{#bold}}{{yay}} :){{/bold}}"};
mstch::map context{
  {"yay", std::string{"Yay!"}},
  {"bold", mstch::lambda{[](const std::string& text, mstch::renderer render) {
    return "<b>" + render(text) + "</b>";
  }}}
};

std::cout << mstch::render(view, context) << std::endl;
```

Output:

```html
<b>Yay! :)</b>
```

### Objects

Custom objects can also be used as context for rendering templates. The class 
must inherit from `mstch::object`, and register it's exported methods with
`register_methods`. Exported methods must have the return type of `mstch::node`.
Objects must be created as a `std::shared_ptr`.

```c++
class example: public mstch::object {
 public:
  example(): m_value(1) {
    register_methods(this, {
      {"count", &example::count},
      {"names", &example::names}  
    });
  }
  
  mstch::node count() {
    return m_value++;
  }
  
  mstch::node names() {
    return mstch::array{
      std::string{"Chris"}, std::string{"Mark"}, std::string{"Scott"}};
  }
  
 private:
  int m_value;
};

std::string view{"{{#names}}<b>{{count}}</b>: {{.}}\n{{/names}}"};
const auto context = std::make_shared<example>();

std::cout << mstch::render(view, context) << std::endl;
```

Output:

```html
<b>1</b>: Chris
<b>2</b>: Mark
<b>3</b>: Scott
```

## Requirements

 - A C++ compiler with decent C++11 support. Currently only tested with GCC 4.9.
 - Boost 1.54+ for [Boost.Variant](http://www.boost.org/doc/libs/1_57_0/doc/html/variant.html)
 - CMake 2.8+ for building

## Installing

From the root of the source tree:

```bash
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
 $ make install
```

## Running the unit tests

Unit tests are using the [Catch](https://github.com/philsquared/Catch) framework, 
included in the repository. [Boost.Program_Options](http://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html) 
and [The Boost Algorithm Library](http://www.boost.org/doc/libs/1_57_0/libs/algorithm/doc/html/index.html)
are also required to build them.

```bash
 $ mkdir build
 $ cd build
 $ cmake -DWITH_UNIT_TESTS=ON ..
 $ make
 $ make test
```
