#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>
#include "mstch/mstch.hpp"

namespace mstch {
    namespace visitor {
        class get_token: public boost::static_visitor<node> {
        public:
            get_token(const std::string& token, const mstch::node& node);
            mstch::node operator()(const boost::blank& blank) const;
            mstch::node operator()(const int& i) const;
            mstch::node operator()(const bool& b) const;
            mstch::node operator()(const std::string& str) const;
            mstch::node operator()(const array& arr) const;
            mstch::node operator()(const map& map) const;
            mstch::node operator()(const std::shared_ptr<object>& obj) const;
        private:
            const std::string& token;
            mstch::node node;
        };
    }
}
