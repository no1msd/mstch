#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "mstch/mstch.hpp"
#include "has_token.hpp"

namespace mstch {

class get_token: public boost::static_visitor<const mstch::node&> {
 public:
  get_token(const std::string& token, const mstch::node& node):
      token(token), node(node)
  {
  }

  template<class T>
  inline const mstch::node& operator()(const T& t) const {
    return node;
  }

 private:
  const std::string& token;
  const mstch::node& node;
};

template<>
inline const mstch::node& get_token::operator()<map>(const map& map) const {
  return map.at(token);
}

template<>
inline const mstch::node& get_token::operator()<std::shared_ptr<object>>(
    const std::shared_ptr<object>& object) const
{
  return object->at(token);
}

}
