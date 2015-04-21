#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>
#include "mstch/mstch.hpp"

namespace mstch {
    namespace visitor {
        class get_token: public boost::static_visitor<const mstch::node&> {
        public:
            get_token(const std::string& token, const mstch::node& node);
            const mstch::node& operator()(const boost::blank& blank) const;
            const mstch::node& operator()(const int& i) const;
            const mstch::node& operator()(const bool& b) const;
            const mstch::node& operator()(const std::string& str) const;
            const mstch::node& operator()(const array& arr) const;
            const mstch::node& operator()(const map& map) const;
            const mstch::node& operator()(const std::shared_ptr<object>& obj) const;
        private:
            const std::string& token;
            const mstch::node& node;
        };
    }
}
