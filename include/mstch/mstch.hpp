#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

#include <boost/variant.hpp>

namespace mstch {

using renderer = std::function<std::string(const std::string&)>;

namespace internal {

template<class N>
class object_t {
 public:
  const N& at(const std::string& name) const {
    cache[name] = (methods.at(name))();
    return cache[name];
  }

  bool has(const std::string name) const {
    return methods.count(name);
  }

 protected:
  template<class S>
  void register_methods(S* s, std::map<std::string,N(S::*)()> methods) {
    for(auto& item: methods)
      this->methods.insert({item.first, std::bind(item.second, s)});
  }

 private:
  std::map<std::string, std::function<N()>> methods;
  mutable std::map<std::string, N> cache;
};

template <typename T>
class is_fun {
 private:
  using not_fun = char;
  using fun_without_args = char[2];
  using fun_with_args = char[3];
  template <typename U, U> struct really_has;
  template <typename C> static fun_without_args& test(
      really_has<std::string(C::*)() const, &C::operator()>*);
  template <typename C> static fun_with_args& test(
      really_has<std::string(C::*)(const std::string&,renderer) const,
      &C::operator()>*);
  template <typename> static not_fun& test(...);

 public:
  static bool const no_args = sizeof(test<T>(0)) == sizeof(fun_without_args);
  static bool const has_args = sizeof(test<T>(0)) == sizeof(fun_with_args);
};

}

class lambda {
 public:
  template<class F>
  lambda(F f, typename std::enable_if<internal::is_fun<F>::no_args>::type* =0):
      fun([f](const std::string&,renderer){return f();})
  {
  }

  template<class F>
  lambda(F f, typename std::enable_if<internal::is_fun<F>::has_args>::type* =0):
      fun(f)
  {
  }

  std::string operator()(
      const std::string& text = "",
      renderer renderer = renderer()) const
  {
    return fun(text, renderer);
  }

 private:
  std::function<std::string(const std::string&, renderer)> fun;
};

using node = boost::make_recursive_variant<
    boost::blank, std::string, int, bool, lambda,
    std::shared_ptr<internal::object_t<boost::recursive_variant_>>,
    std::map<const std::string, boost::recursive_variant_>,
    std::vector<boost::recursive_variant_>>::type;
using object = internal::object_t<node>;
using map = std::map<const std::string, node>;
using array = std::vector<node>;

std::string render(
    const std::string& tmplt,
    const node& root,
    const std::map<std::string,std::string>& partials =
        std::map<std::string,std::string>());

}
