#include "get_token.hpp"

using namespace mstch;
using namespace mstch::visitor;

get_token::get_token(const std::string& token, const mstch::node& node):
        token(token), node(node)
{
}

std::pair<bool,node> get_token::operator()(const boost::blank& blank) const {
    return {token == ".", node};
}

std::pair<bool,node> get_token::operator()(const int& i) const {
    return {token == ".", node};
}

std::pair<bool,node> get_token::operator()(const bool& b) const {
    return {token == ".", node};
}

std::pair<bool,node> get_token::operator()(const std::string& str) const {
    return {token == ".", node};
}

std::pair<bool,node> get_token::operator()(const array& arr) const {
    return {token == ".", node};
}

std::pair<bool,node> get_token::operator()(const map& map) const {
    if(map.count(token) == 1)
        return {true, map.at(token)};
    else
        return {false, node};
}

std::pair<bool,node> get_token::operator()(const std::shared_ptr<object>& obj) const {
    if (obj->has(token))
        return {true, obj->at(token)};
    else
        return {false, node};
}
