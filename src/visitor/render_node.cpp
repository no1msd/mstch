#include <utils.h>
#include "render_node.h"

using namespace mstch;

visitor::render_node::render_node(bool html_escaped):
        html_escaped(html_escaped)
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
    return html_escaped?html_escape(str):str;
}

std::string visitor::render_node::operator()(const array& arr) const {
    return "";
}

std::string visitor::render_node::operator()(const object& obj) const {
    return "";
}
