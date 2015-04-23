#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "mstch/mstch.hpp"

namespace mstch {
namespace visitor {

class has_token: public boost::static_visitor<bool> {
 public:
  has_token(const std::string& token): token(token) {
  }

  template<class T>
  inline bool operator()(const T& t) const {
    return token == ".";
  }
private:
  const std::string& token;
};

template<>
inline bool has_token::operator()<map>(const map& map) const {
  return map.count(token) == 1;
}

template<>
inline bool has_token::operator()<std::shared_ptr<object>>(
        const std::shared_ptr<object>& object) const
{
  return object->has(token);
}

}
}
