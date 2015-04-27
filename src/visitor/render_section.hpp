#pragma once

#include <boost/variant/static_visitor.hpp>

#include "render_context.hpp"
#include "mstch/mstch.hpp"
#include "utils.hpp"

namespace mstch {

class render_section: public boost::static_visitor<std::string> {
 public:
  enum class flag { none, keep_array };
  render_section(
      render_context& ctx,
      const template_type& section,
      flag p_flag = flag::none):
      ctx(ctx), section(section), m_flag(p_flag)
  {
  }

  template<class T>
  inline std::string operator()(const T& t) const {
    return render_context::push(ctx, t).render(section);
  }

 private:
  render_context& ctx;
  const template_type& section;
  flag m_flag;
};

template<>
inline std::string render_section::operator()(const lambda& fun) const {
  std::string section_str;
  for(auto& token: section)
    section_str += token.raw();

  return fun(section_str, [this](const std::string& str) {
    return render_context::push(ctx).render(template_type{str});
  });
}

template<>
inline std::string render_section::operator()(const array& array) const {
  std::string out;
  if(m_flag == flag::keep_array)
    return render_context::push(ctx, array).render(section);
  else
    for (auto& item: array)
      out += visit(render_section(ctx, section, flag::keep_array), item);
  return out;
}

}
