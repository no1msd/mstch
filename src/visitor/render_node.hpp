#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "mstch/mstch.hpp"
#include <set>

namespace mstch {
    namespace visitor {
        class render_node: public boost::static_visitor<std::string> {
        public:
            enum class flag { escape_html };
            render_node(std::set<flag> flags = {});
            std::string operator()(const boost::blank& blank) const;
            std::string operator()(const int& i) const;
            std::string operator()(const bool& b) const;
            std::string operator()(const std::string& str) const;
            std::string operator()(const array& arr) const;
            std::string operator()(const object& obj) const;
            std::string operator()(const string_lambda& lambda) const;
            std::string operator()(const renderer_lambda& lambda) const;
        private:
            std::set<flag> flags;
        };
    }
}
