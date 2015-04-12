#ifndef _MSTCH_IS_NODE_EMPTY_H_
#define _MSTCH_IS_NODE_EMPTY_H_

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "mstch/mstch.hpp"

namespace mstch {
    namespace visitor {
        class is_node_empty: public boost::static_visitor<bool> {
        public:
            bool operator()(const boost::blank& blank) const;
            bool operator()(const int& i) const;
            bool operator()(const bool& b) const;
            bool operator()(const std::string& str) const;
            bool operator()(const array& arr) const;
            bool operator()(const object& obj) const;
        };
    }
}

#endif //_MSTCH_IS_NODE_EMPTY_H_
