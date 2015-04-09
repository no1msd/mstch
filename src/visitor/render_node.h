#ifndef _MSTCH_RENDER_NODE_H_
#define _MSTCH_RENDER_NODE_H_

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>

#include "types.h"

namespace mstch {
    namespace visitor {
        class render_node: public boost::static_visitor<std::string> {
        private:
            bool html_escaped;
        public:
            render_node(bool html_escaped);
            std::string operator()(const boost::blank& blank) const;
            std::string operator()(const int& i) const;
            std::string operator()(const bool& b) const;
            std::string operator()(const std::string& str) const;
            std::string operator()(const array& arr) const;
            std::string operator()(const object& obj) const;
        };
    }
}

#endif //_MSTCH_RENDER_NODE_H_
