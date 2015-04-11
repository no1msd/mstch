#include "render_context.h"
#include "state/render_state.h"
#include "state/outside_section.h"

#include <regex>
#include <visitor/to_json.h>

using namespace mstch;

const mstch::node render_context::null_node;

render_context::render_context(
        const mstch::object& object,
        const std::map<std::string,std::string>& partials):
        partials(partials),
        objects{object},
        state(new state::outside_section)
{
}

render_context::render_context(
        const mstch::object& object,
        const render_context& context):
        partials(context.partials),
        objects(context.objects),
        state(new state::outside_section)
{
    objects.push_front(object);
}

const mstch::node& render_context::find_node(
        const std::string& token,
        const std::deque<object>& current_objects)
{
    if (token != "." && token.find('.') != std::string::npos) {
        return find_node(
                token.substr(token.rfind('.') + 1),
                {boost::get<object>(find_node(
                        token.substr(0, token.rfind('.')),
                        current_objects))});
    } else {
        for (auto& object: current_objects)
            if (object.count(token) != 0)
                return object.at(token);
        return null_node;
    }
}

const mstch::node& render_context::get_node(const std::string& token) {
    return find_node(token, objects);
}

std::string render_context::render(const std::string& t) {
    std::ostringstream output;
    auto re = std::regex("\\{{2}[^\\}]*\\}{2}|\\{{3}[^\\}]*\\}{3}");
    std::sregex_token_iterator it(t.begin(), t.end(), re, {-1, 0});
    for (; it != std::sregex_token_iterator(); ++it)
        output << state->render(*this, token(it->str()));
    return output.str();
}
