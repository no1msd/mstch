#include "visitor/is_node_empty.h"
#include "visitor/render_section.h"
#include "in_section.h"
#include "outside_section.h"

using namespace mstch;

state::in_section::in_section(const std::string& section_name):
        section_name(section_name), skipped_openings(0)
{
}

std::string state::in_section::render(
        render_context& ctx,
        const token& token)
{
    switch(token.type()) {
    case token_type::section_close:
        if(token.content() == section_name && skipped_openings == 0) {
            auto section_node = ctx.get_node(section_name);
            std::string out("");
            if (!boost::apply_visitor(visitor::is_node_empty(), section_node))
                out = boost::apply_visitor(
                        visitor::render_section(ctx, section_text.str()),
                        section_node);
            ctx.set_state<outside_section>();
            return out;
        } else {
            skipped_openings--;
            section_text << token.raw();
        }
        break;
    case token_type::inverted_section_open:
    case token_type::section_open:
        skipped_openings++;
    case token_type::text:
    case token_type::variable:
    case token_type::unescaped_variable:
    case token_type::comment:
    case token_type::partial:
        section_text << token.raw();
        break;
    }
    return "";
}
