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

std::string render_context::push::render(const std::vector<token>& tokens) {
    return context.render(tokens);
}

render_context::render_context(
        const mstch::object& object,
        const std::map<std::string,std::string>& partials):
        partials{partials},
        objects{object},
        delim_start{"{{"},
        delim_end{"}}"}
{
    state.push(std::unique_ptr<state::render_state>(new state::outside_section));
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

void render_context::tokenize(const std::string& t, std::vector<token>& toks) {
    std::string::const_iterator tok_end, tok_start = t.begin();
    parse_state pstate = parse_state::start;
    unsigned int del_pos = 0;
    bool ws_only = true;
    for (std::string::const_iterator it = t.begin(); it != t.end(); ++it) {
        if (pstate == parse_state::start) {
            if (*it == delim_start[0]) {
                pstate = parse_state::in_del_start;
                tok_end = it;
                del_pos = 1;
            } else if(*it == '\n') {
                toks.push_back({false, true, ws_only, {tok_start, it + 1}});
                ws_only = true;
                tok_start = it + 1;
            } else if (*it != ' ' && *it != '\t') {
                ws_only = false;
            }
        } else if(pstate == parse_state::in_del_start) {
            if (*it == delim_start[del_pos] && ++del_pos == delim_start.size())
                pstate = parse_state::in_del;
            else
                pstate = parse_state::start;
        } else if(pstate == parse_state::in_del) {
            if (*it== '{') {
                pstate = parse_state::in_esccontent;
            } else if (*it == delim_end[0]) {
                pstate = parse_state::in_del_end;
                del_pos = 1;
            } else {
                pstate = parse_state::in_content;
            }
        } else if(pstate == parse_state::in_esccontent && *it == '}') {
            pstate = parse_state::in_content;
        } else if(pstate == parse_state::in_content && *it == delim_end[0]) {
            pstate = parse_state::in_del_end;
            del_pos = 1;
        } else if(pstate == parse_state::in_del_end) {
            if (*it == delim_end[del_pos] && ++del_pos == delim_end.size()) {
                pstate = parse_state::start;
                toks.push_back({false, false, ws_only, {tok_start, tok_end}});
                toks.push_back({true, false, false,
                      {tok_end +delim_start.size(), it - delim_end.size() +1}});
                ws_only = true;
                tok_start = it + 1;
            } else {
                pstate = parse_state::start;
            }
        }
    }
    toks.push_back({false, false, ws_only, {tok_start, t.end()}});
}

void render_context::strip_whitespace(std::vector<token>& tokens) {
    auto line_begin = tokens.begin();
    bool has_tag = false, non_space = false;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        auto type = (*it).token_type();
        if (type != token::type::text && type != token::type::variable &&
                type != token::type::unescaped_variable)
            has_tag = true;
        else if (!(*it).is_ws_only())
            non_space = true;
        if ((*it).is_eol()) {
            if (has_tag && !non_space)
                for (auto line_it = line_begin; line_it != it + 1; ++line_it)
                    if ((*line_it).is_ws_only())
                        (*line_it).mark();
            non_space = has_tag = false;
            line_begin = it + 1;
        }
    }
    for (auto it = tokens.begin(); it != tokens.end();)
        ((*it).is_marked())?(it = tokens.erase(it)):(++it);
}

std::string render_context::render(const std::string& tmplt) {
    std::vector<token> tokens;
    tokenize(tmplt, tokens);
    strip_whitespace(tokens);
    return render(tokens);
}

std::string render_context::render(const std::vector<token>& tokens) {
    std::string output;
    for (auto& token: tokens)
        output += state.top()->render(*this, token);
    return output;
}

std::string render_context::render_partial(const std::string& partial_name) {
    return (partials.count(partial_name))?render(partials.at(partial_name)):"";
}
