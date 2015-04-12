#include "utils.hpp"
#include "render_node.hpp"

using namespace mstch;

visitor::render_node::render_node(std::set<flag> flags):
        flags(flags)
{
}

std::string visitor::render_node::operator()(const boost::blank& blank) const {
    return "";
}

std::string visitor::render_node::operator()(const int& i) const {
    return std::to_string(i);
}

std::string visitor::render_node::operator()(const bool& b) const {
    return b?"true":"false";
}

std::string visitor::render_node::operator()(const std::string& str) const {
    return (flags.find(flag::escape_html) != flags.end())?html_escape(str):str;
}

std::string visitor::render_node::operator()(const array& arr) const {
    return "";
}

std::string visitor::render_node::operator()(const object& obj) const {
    return "";
}

std::string visitor::render_node::operator()(
        const string_lambda& lambda) const
{
    return this->operator()(lambda());
}

std::string visitor::render_node::operator()(
        const renderer_lambda& lambda) const
{
    return this->operator()((lambda())("", [](const std::string& text) {
        return std::string{""};
    }));
}
