#include "render_context.hpp"
#include "utils.hpp"
#include "state/outside_section.hpp"

using namespace mstch;

const mstch::node render_context::null_node;

render_context::push::push(render_context& context, const mstch::object& obj):
        context(context)
{
    context.objects.emplace_front(obj);
    context.state.push(std::unique_ptr<state::render_state>(
            new state::outside_section));
}

render_context::push::~push() {
    context.objects.pop_front();
    context.state.pop();
}

std::string render_context::push::render(const template_type& templt) {
    return context.render(templt);
}

render_context::render_context(
        const mstch::object& object,
        const std::map<std::string,template_type>& partials):
        partials{partials},
        objects{object}
{
    state.push(std::unique_ptr<state::render_state>(
            new state::outside_section));
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

std::string render_context::render(const template_type& templt) {
    std::string output;
    for (auto& token: templt)
        output += state.top()->render(*this, token);
    return output;
}

std::string render_context::render_partial(const std::string& partial_name) {
    return (partials.count(partial_name))?render(partials.at(partial_name)):"";
}
