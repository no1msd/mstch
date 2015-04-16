#include "is_node_empty.hpp"

using namespace mstch;
using namespace mstch::visitor;

bool is_node_empty::operator()(const boost::blank& blank) const {
    return true;
}

bool is_node_empty::operator()(const int& i) const {
    return i == 0;
}

bool is_node_empty::operator()(const bool& b) const {
    return !b;
}

bool is_node_empty::operator()(const std::string& str) const {
    return str == "";
}

bool is_node_empty::operator()(const array& arr) const {
    return arr.size() == 0;
}

bool is_node_empty::operator()(const map& map) const {
    return false;
}

bool is_node_empty::operator()(const std::shared_ptr<object>& obj) const {
    return false;
}
