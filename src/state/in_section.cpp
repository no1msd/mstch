#include "in_section.hpp"
#include "outside_section.hpp"
#include "visitor/is_node_empty.hpp"
#include "visitor/render_section.hpp"

using namespace mstch;

state::in_section::in_section(type type, const std::string& section_name):
    m_type(type), section_name(section_name), skipped_openings(0)
{
}

std::string state::in_section::render(render_context& ctx, const token& token) {
  if(token.token_type() == token::type::section_close)
    if(token.name() == section_name && skipped_openings == 0) {
      auto& sn = ctx.get_node(section_name);
      std::string out;
      if(m_type == type::normal &&
          !boost::apply_visitor(visitor::is_node_empty(), sn))
        out = boost::apply_visitor(visitor::render_section(ctx, section), sn);
      else if(m_type == type::inverted &&
          boost::apply_visitor(visitor::is_node_empty(), sn))
        out = render_context::push(ctx).render(section);
      ctx.set_state<outside_section>();
      return out;
    } else
      skipped_openings--;
  else if(token.token_type() == token::type::inverted_section_open ||
      token.token_type() == token::type::section_open)
    skipped_openings++;
  section << token;
  return "";
}
