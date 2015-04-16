#include "has_token.hpp"

using namespace mstch;
using namespace mstch::visitor;

has_token::has_token(const std::string& token): token(token) {
}

bool has_token::operator()(const boost::blank& blank) const {
    return false;
}

bool has_token::operator()(const int& i) const {
    return token == ".";
}

bool has_token::operator()(const bool& b) const {
    return token == ".";
}

bool has_token::operator()(const std::string& str) const {
    return token == ".";
}

bool has_token::operator()(const array& arr) const {
    return token == ".";
}

bool has_token::operator()(const map& map) const {
    return map.count(token) == 1;
}

bool has_token::operator()(const std::shared_ptr<object>& obj) const {
    return obj->has(token);
}
