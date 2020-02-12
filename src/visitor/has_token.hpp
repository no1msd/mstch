#pragma once

#include "mstch/mstch.hpp"

namespace mstch {

class has_token {
public:
    has_token(const std::string& token) : m_token(token) {}

    template<class T>
    bool operator()(const T&) const {
        return m_token == ".";
    }

    bool operator()(const map_wrapper& map) const { return map.values.count(m_token) == 1; }

    bool operator()(const object_wrapper& object) const { return object.values->has(m_token); }

private:
    const std::string& m_token;
};

}  // namespace mstch
