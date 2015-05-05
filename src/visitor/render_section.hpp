#pragma once

#include <boost/variant/static_visitor.hpp>

#include "render_context.hpp"
#include "mstch/mstch.hpp"
#include "utils.hpp"
#include "render_node.hpp"

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
  std::string operator()(const T& t) const {
    return render_context::push(ctx, t).render(section);
  }

  std::string operator()(const lambda& fun) const {
    std::string section_str;
    for(auto& token: section)
      section_str += token.raw();
    template_type interpreted{fun([this](const mstch::node& n) {
      return visit(render_node(ctx), n);
    }, section_str)};
    return render_context::push(ctx).render(interpreted);
  }

  std::string operator()(const array& array) const {
    std::string out;
    if(m_flag == flag::keep_array)
      return render_context::push(ctx, array).render(section);
    else
      for (auto& item: array)
        out += visit(render_section(ctx, section, flag::keep_array), item);
    return out;
  }

 private:
  render_context& ctx;
  const template_type& section;
  flag m_flag;
};

}
