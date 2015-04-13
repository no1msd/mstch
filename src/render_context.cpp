#include "render_context.hpp"
#include "utils.hpp"
#include "state/outside_section.hpp"
#include <regex>

using namespace mstch;

const mstch::node render_context::null_node;

render_context::push::push(render_context& context, const mstch::object& obj):
        context(context)
{
    context.objects.push_front(obj);
    context.push_state<state::outside_section>();
}

render_context::push::~push() {
    context.objects.pop_front();
    context.state.pop();
}

std::string render_context::push::render(const std::string& tmplt) {
    return context.render(tmplt);
}

render_context::render_context(
        const mstch::object& object,
        const std::map<std::string,std::string>& partials):
        partials{partials},
        objects{object}
{
    push_state<state::outside_section>();
    for(auto& partial: this->partials)
        partial.second = strip_whitespace(partial.second);
}

const mstch::node& render_context::find_node(
        const std::string& token,
        const std::deque<object>& current_objects)
{
    if (token != "." && token.find('.') != std::string::npos)
        return find_node(
                token.substr(token.rfind('.') + 1),
                {boost::get<object>(find_node(
                        token.substr(0, token.rfind('.')),
                        current_objects))});
    else
        for (auto& object: current_objects)
            if (object.count(token))
                return object.at(token);
    return null_node;
}

const mstch::node& render_context::get_node(const std::string& token) {
    return find_node(token, objects);
}

std::string render_context::render(const std::string& t) {
    std::ostringstream output;
    auto re = std::regex("\\{{2}[^\\}]*\\}{2}|\\{{3}[^\\}]*\\}{3}");
    std::sregex_token_iterator it(t.begin(), t.end(), re, {-1, 0});
    for (; it != std::sregex_token_iterator(); ++it)
        output << state.top()->render(*this, token(it->str()));
    return output.str();
}

std::string render_context::render_partial(const std::string& partial_name) {
    return (partials.count(partial_name))?render(partials.at(partial_name)):"";
}
