#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "mstch/mstch.hpp"

namespace mstch {
namespace visitor {

class is_node_empty: public boost::static_visitor<bool> {
 public:
  template<class T> inline
  bool operator()(const T& t) const {
    return false;
  }
};

template<>
inline bool is_node_empty::operator()<boost::blank>(
    const boost::blank& blank) const
{
  return true;
}

template<>
inline bool is_node_empty::operator()<int>(const int& val) const {
  return val == 0;
}

template<>
inline bool is_node_empty::operator()<bool>(const bool& val) const {
  return !val;
}

template<>
inline bool is_node_empty::operator()<std::string>(
    const std::string& val) const
{
  return val == "";
}

template<>
inline bool is_node_empty::operator()<array>(const array& array) const {
  return array.size() == 0;
}

}
}
