#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>
#include "mstch/mstch.hpp"

namespace mstch {
    namespace visitor {
        class has_token: public boost::static_visitor<bool> {
        public:
            has_token(const std::string& token);
            bool operator()(const boost::blank& blank) const;
            bool operator()(const int& i) const;
            bool operator()(const bool& b) const;
            bool operator()(const std::string& str) const;
            bool operator()(const array& arr) const;
            bool operator()(const map& map) const;
            bool operator()(const std::shared_ptr<object>& obj) const;
        private:
            const std::string& token;
        };
    }
}
