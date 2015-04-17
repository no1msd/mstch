#include "visitor/render_node.hpp"
#include "outside_section.hpp"
#include "in_section.hpp"
#include "in_inverted_section.hpp"
#include "render_context.hpp"

using namespace mstch;
using flag = visitor::render_node::flag;

std::string state::outside_section::render(
        render_context& ctx, const token& token)
{
    switch(token.token_type()) {
    case token::type::section_open:
        ctx.set_state<in_section>(token.content());
        break;
    case token::type::inverted_section_open:
        ctx.set_state<in_inverted_section>(token.content());
        break;
    case token::type::variable:
    case token::type::unescaped_variable: {
        auto visitor = visitor::render_node((token.token_type() ==
            token::type::variable)?flag::escape_html:flag::none);
        auto node = ctx.get_node(token.content());
        return boost::apply_visitor(visitor, node);
    }
    case token::type::comment: break;
    case token::type::text:
        return token.content();
    case token::type::partial:
        return ctx.render_partial(token.content());
    case token::type::section_close: break;
    }
    return "";
}
