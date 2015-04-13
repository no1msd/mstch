#include "render_section.hpp"

using namespace mstch;

visitor::render_section::render_section(
        render_context& ctx, const std::vector<token>& section_tokens, std::set<flag> flags):
        ctx(ctx), section_tokens(section_tokens), flags(flags)
{
}

std::string visitor::render_section::operator()(
        const boost::blank& blank) const
{
    return render_context::push(ctx, {{".", {}}}).render(section_tokens);
}

std::string visitor::render_section::operator()(const int& i) const {
    return render_context::push(ctx, {{".", i}}).render(section_tokens);
}

std::string visitor::render_section::operator()(const bool& b) const {
    return render_context::push(ctx, {{".", b}}).render(section_tokens);
}

std::string visitor::render_section::operator()(const std::string& str) const {
    return render_context::push(ctx, {{".", str}}).render(section_tokens);
}

std::string visitor::render_section::operator()(const object& obj) const {
    return render_context::push(ctx, obj).render(section_tokens);
}

std::string visitor::render_section::operator()(const array& a) const {
    std::string out;
    if(flags.find(flag::keep_array) != flags.end())
        out += render_context::push(ctx, {{".", a}}).render(section_tokens);
    else
        for (auto& item: a)
            out += boost::apply_visitor(
                    render_section(ctx, section_tokens, {flag::keep_array}), item);
    return out;
}

std::string visitor::render_section::operator()(
        const string_lambda& lambda) const
{
    return lambda();
}

std::string visitor::render_section::operator()(
        const renderer_lambda& lambda) const
{
    return "";
    /*return (lambda())(section_tokens, [&](const std::string& text) {
        return render_context::push(ctx).render(text);
    }); TODO ! */
}
