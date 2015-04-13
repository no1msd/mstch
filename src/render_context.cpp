#include "render_context.hpp"
#include "utils.hpp"
#include "state/outside_section.hpp"

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

std::string render_context::push::render(const std::vector<token>& tokens) {
    return context.render(tokens);
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

enum class parse_state {
    start, in_del_start, in_del, in_content, in_escaped_content, in_del_end
};

std::string render_context::render(const std::string& t) {
    const std::string delim_start{"{{"};
    const std::string delim_end{"}}"};
    std::string out;
    std::string::const_iterator tok_end, tok_start = t.begin();
    parse_state pstate = parse_state::start;
    unsigned int delim_p = 0;
    for (std::string::const_iterator it = t.begin(); it != t.end(); ++it) {
        if(pstate == parse_state::start && *it == delim_start[0]) {
            pstate = parse_state::in_del_start;
            tok_end = it;
            delim_p = 1;
        } else if(pstate == parse_state::in_del_start) {
            if (*it == delim_start[delim_p] && ++delim_p == delim_start.size())
                pstate = parse_state::in_del;
            else
                pstate = parse_state::start;
        } else if(pstate == parse_state::in_del) {
            if (*it== '{') {
                pstate = parse_state::in_escaped_content;
            } else if (*it == delim_end[0]) {
                pstate = parse_state::in_del_end;
                delim_p = 1;
            } else {
                pstate = parse_state::in_content;
            }
        } else if(pstate == parse_state::in_escaped_content && *it == '}') {
            pstate = parse_state::in_content;
        } else if(pstate == parse_state::in_content && *it == delim_end[0]) {
            pstate = parse_state::in_del_end;
            delim_p = 1;
        } else if(pstate == parse_state::in_del_end) {
            if (*it == delim_end[delim_p] && ++delim_p == delim_end.size()) {
                pstate = parse_state::start;
                out += state.top()->render(*this, {false, {tok_start,tok_end}});
                out += state.top()->render(*this, {true, {tok_end, it + 1}});
                tok_start = it + 1;
            } else {
                pstate = parse_state::start;
            }
        }
    }
    out += state.top()->render(*this, {false, {tok_start, t.end()}});
    return out;
}

std::string render_context::render(const std::vector<token>& tokens) {
    std::string output;
    for(auto& token: tokens)
        output += state.top()->render(*this, token);
    return output;
}

std::string render_context::render_partial(const std::string& partial_name) {
    return (partials.count(partial_name))?render(partials.at(partial_name)):"";
}
