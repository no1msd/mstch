#include "get_token.hpp"

using namespace mstch;
using namespace mstch::visitor;

get_token::get_token(const std::string& token, const mstch::node& node):
        token(token), node(node)
{
}

mstch::node get_token::operator()(const boost::blank& blank) const {
    return node;
}

mstch::node get_token::operator()(const int& i) const {
    return node;
}

mstch::node get_token::operator()(const bool& b) const {
    return node;
}

mstch::node get_token::operator()(const std::string& str) const {
    return node;
}

mstch::node get_token::operator()(const array& arr) const {
    return node;
}

mstch::node get_token::operator()(const map& map) const {
    return map.at(token);
}

mstch::node get_token::operator()(const std::shared_ptr<object>& obj) const {
    return obj->at(token);
}
