#include "utils.hpp"
#include "render_node.hpp"

using namespace mstch;
using namespace mstch::visitor;

render_node::render_node(flag p_flag): m_flag(p_flag) {
}

std::string render_node::operator()(const boost::blank& blank) const {
    return "";
}

std::string render_node::operator()(const int& i) const {
    return std::to_string(i);
}

std::string render_node::operator()(const bool& b) const {
    return b?"true":"false";
}

std::string render_node::operator()(const std::string& str) const {
    return (m_flag == flag::escape_html)?html_escape(str):str;
}

std::string render_node::operator()(const array& arr) const {
    return "";
}

std::string render_node::operator()(const map& map) const {
    return "";
}

std::string render_node::operator()(const std::shared_ptr<object>& obj) const {
    return "";
}
