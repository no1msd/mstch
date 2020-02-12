#pragma once

#include "mstch/mstch.hpp"

namespace mstch {

class is_node_empty {
public:
    template<class T>
    bool operator()(const T&) const {
        return false;
    }

    bool operator()(const std::nullptr_t&) const { return true; }

    bool operator()(const int& value) const { return value == 0; }

    bool operator()(const double& value) const { return value == 0; }

    bool operator()(const bool& value) const { return !value; }

    bool operator()(const std::string& value) const { return value == ""; }

    bool operator()(const array_wrapper& array) const { return array.values.size() == 0; }
};

}  // namespace mstch
