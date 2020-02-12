#pragma once

#include "has_token.hpp"
#include "mstch/mstch.hpp"

namespace mstch {

class get_token {
public:
    get_token(const std::string& token, const mstch::node& node)
        : m_token(token), m_node(node)
    {}

    template<class T>
    const mstch::node& operator()(const T&) const {
        return m_node;
    }

    const mstch::node& operator()(const map_wrapper& map) const {
        return map.values.at(m_token);
    }

    const mstch::node& operator()(const object_wrapper& object) const {
        return object.values->at(m_token);
    }

private:
    const std::string& m_token;
    const mstch::node& m_node;
};

}  // namespace mstch
