#include "in_section.hpp"
#include "outside_section.hpp"
#include "visitor/is_node_empty.hpp"
#include "visitor/render_section.hpp"

using namespace mstch;

state::in_section::in_section(const std::string& section_name):
        section_name(section_name), skipped_openings(0)
{
}

std::string state::in_section::render(render_context& ctx, const token& token) {
    switch(token.token_type()) {
    case token::type::section_close:
        if(token.content() == section_name && skipped_openings == 0) {
            auto section_node = ctx.get_node(section_name);
            std::string out;
            if (!boost::apply_visitor(visitor::is_node_empty(), section_node))
                out = boost::apply_visitor(
                        visitor::render_section(ctx, section), section_node);
            ctx.set_state<outside_section>();
            return out;
        } else {
            skipped_openings--;
            section << token;
        }
        break;
    case token::type::inverted_section_open:
    case token::type::section_open:
        skipped_openings++;
    case token::type::text:
    case token::type::variable:
    case token::type::unescaped_variable:
    case token::type::comment:
    case token::type::partial:
        section << token;
        break;
    }
    return "";
}
