#include "to_json.hpp"

using namespace mstch;

std::string visitor::to_json::operator()(const boost::blank& blank) const {
    return "";
}

std::string visitor::to_json::operator()(const int& i) const {
    return std::to_string(i);
}

std::string visitor::to_json::operator()(const bool& b) const {
    return b?"true":"false";
}

std::string visitor::to_json::operator()(const std::string& str) const {
    return "\"" + str + "\"";
}

std::string visitor::to_json::operator()(const array& arr) const {
    bool first = true;
    std::ostringstream out;
    out << "[";
    for(auto& item: arr) {
        first?(first = false):(out << ", ");
        out << boost::apply_visitor(*this, item);
    }
    out << "]";
    return out.str();
}

std::string visitor::to_json::operator()(const object& obj) const {
    bool first = true;
    std::ostringstream out;
    out << "{";
    for(auto& item: obj) {
        first?(first = false):(out << ", ");
        out << item.first << ": " << boost::apply_visitor(*this, item.second);
    }
    out << "}";
    return out.str();
}
