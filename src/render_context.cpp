#include "render_context.hpp"
#include "utils.hpp"
#include "state/outside_section.hpp"
#include "visitor/get_token.hpp"
#include "visitor/has_token.hpp"

using namespace mstch;

const mstch::node render_context::null_node;

render_context::push::push(render_context& context, const mstch::node& node):
        context(context)
{
    context.nodes.emplace_front(node);
    context.state.push(std::unique_ptr<state::render_state>(
            new state::outside_section));
}

render_context::push::~push() {
    context.nodes.pop_front();
    context.state.pop();
}

std::string render_context::push::render(const template_type& templt) {
    return context.render(templt);
}

render_context::render_context(
        const mstch::node& node,
        const std::map<std::string,template_type>& partials):
        partials{partials},
        nodes{node}
{
    state.push(std::unique_ptr<state::render_state>(
            new state::outside_section));
}

const mstch::node& render_context::find_node(
        const std::string& token,
        const std::deque<node>& current_nodes)
{
    if (token != "." && token.find('.') != std::string::npos)
        return find_node(
                token.substr(token.rfind('.') + 1),
                {find_node(token.substr(0, token.rfind('.')), current_nodes)});
    else
        for (auto& n: current_nodes)
            if (boost::apply_visitor(visitor::has_token(token), n))
                return boost::apply_visitor(visitor::get_token(token, n), n);
    return null_node;
}

const mstch::node& render_context::get_node(const std::string& token) {
    return find_node(token, nodes);
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
