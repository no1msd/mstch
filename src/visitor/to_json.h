#ifndef _MSTCH_TO_JSON_H_
#define _MSTCH_TO_JSON_H_

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>
#include <render_context.h>

#include "mstch/mstch.h"

namespace mstch {
    namespace visitor {
        class to_json: public boost::static_visitor<std::string> {
        public:
            std::string operator()(const boost::blank& blank) const;
            std::string operator()(const int& i) const;
            std::string operator()(const bool& b) const;
            std::string operator()(const std::string& str) const;
            std::string operator()(const array& arr) const;
            std::string operator()(const object& obj) const;
        };
    }
}

#endif //_MSTCH_TO_JSON_H_
