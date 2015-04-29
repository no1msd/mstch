#pragma once

#include <boost/variant/static_visitor.hpp>

#include "mstch/mstch.hpp"

namespace mstch {

class is_node_empty: public boost::static_visitor<bool> {
 public:
  template<class T>
  inline bool operator()(const T& t) const {
    return false;
  }
};

template<>
inline bool is_node_empty::operator()(const std::nullptr_t& nul) const {
  return true;
}

template<>
inline bool is_node_empty::operator()(const int& value) const {
  return value == 0;
}

template<>
inline bool is_node_empty::operator()(const double& value) const {
  return value == 0;
}

template<>
inline bool is_node_empty::operator()(const bool& value) const {
  return !value;
}

template<>
inline bool is_node_empty::operator()(const std::string& value) const {
  return value == "";
}

template<>
inline bool is_node_empty::operator()(const array& array) const {
  return array.size() == 0;
}

}
