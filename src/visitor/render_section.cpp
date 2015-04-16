#include "render_section.hpp"

using namespace mstch;
using namespace mstch::visitor;

render_section::render_section(
        render_context& ctx, const template_type& section, flag p_flag):
        ctx(ctx), section(section), m_flag(p_flag)
{
}

std::string render_section::operator()(
        const boost::blank& blank) const
{
    return render_context::push(ctx, mstch::node{}).render(section);
}

std::string render_section::operator()(const int& i) const {
    return render_context::push(ctx, i).render(section);
}

std::string render_section::operator()(const bool& b) const {
    return render_context::push(ctx, b).render(section);
}

std::string render_section::operator()(const std::string& str) const {
    return render_context::push(ctx, str).render(section);
}

std::string render_section::operator()(const map& map) const {
    return render_context::push(ctx, map).render(section);
}

std::string render_section::operator()(const array& a) const {
    std::string out;
    if(m_flag == flag::keep_array)
        out += render_context::push(ctx, a).render(section);
    else
        for (auto& item: a)
            out += boost::apply_visitor(
                    render_section(ctx, section, flag::keep_array), item);
    return out;
}

std::string render_section::operator()(const std::shared_ptr<object>& obj) const {
    return render_context::push(ctx, obj).render(section);
}
