#ifndef _MSTCH_RENDER_SECTION_H_
#define _MSTCH_RENDER_SECTION_H_

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>
#include "render_context.hpp"
#include <set>

#include "mstch/mstch.hpp"

namespace mstch {
    namespace visitor {
        class render_section: public boost::static_visitor<std::string> {
        public:
            enum class flag { keep_array };
        private:
            render_context& context;
            std::string section;
            std::set<flag> flags;
        public:
            render_section(
                    render_context& context,
                    const std::string& section,
                    std::set<flag> flags = {});
            std::string operator()(const boost::blank& blank) const;
            std::string operator()(const int& i) const;
            std::string operator()(const bool& b) const;
            std::string operator()(const std::string& str) const;
            std::string operator()(const array& arr) const;
            std::string operator()(const object& obj) const;
        };
    }
}

#endif //_MSTCH_RENDER_SECTION_H_
