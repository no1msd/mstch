#include "is_node_empty.hpp"

using namespace mstch;

bool visitor::is_node_empty::operator()(const boost::blank& blank) const {
    return true;
}

bool visitor::is_node_empty::operator()(const int& i) const {
    return i == 0;
}

bool visitor::is_node_empty::operator()(const bool& b) const {
    return !b;
}

bool visitor::is_node_empty::operator()(const std::string& str) const {
    return str == "";
}

bool visitor::is_node_empty::operator()(const array& arr) const {
    return arr.size() == 0;
}

bool visitor::is_node_empty::operator()(const object& obj) const {
    return false;
}

bool visitor::is_node_empty::operator()(const string_lambda& lambda) const {
    return false; // TODO
}

bool visitor::is_node_empty::operator()(const renderer_lambda& lambda) const {
    return false; // TODO
}
