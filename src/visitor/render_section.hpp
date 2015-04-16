#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/blank.hpp>
#include "render_context.hpp"
#include "mstch/mstch.hpp"

namespace mstch {
    namespace visitor {
        class render_section: public boost::static_visitor<std::string> {
        public:
            enum class flag { none, keep_array };
            render_section(
                    render_context& ctx,
                    const template_type& section,
                    flag p_flag = flag::none);
            std::string operator()(const boost::blank& blank) const;
            std::string operator()(const int& i) const;
            std::string operator()(const bool& b) const;
            std::string operator()(const std::string& str) const;
            std::string operator()(const array& arr) const;
            std::string operator()(const map& map) const;
            std::string operator()(const std::shared_ptr<object>& obj) const;
        private:
            render_context& ctx;
            const template_type& section;
            flag m_flag;
        };
    }
}
