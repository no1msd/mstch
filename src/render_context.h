#ifndef _MSTCH_RENDER_CONTEXT_H_
#define _MSTCH_RENDER_CONTEXT_H_

#include <deque>
#include <sstream>
#include <string>

#include "mstch/mstch.h"
#include "state/render_state.h"

namespace mstch {
    class render_context {
    private:
        static const mstch::node null_node;
        const mstch::node& find_node(
                const std::string& token,
                const std::deque<object>& current_objects);
        const std::map<std::string,std::string>& partials;
        std::deque<mstch::object> objects;
        std::unique_ptr<state::render_state> state;
    public:
        render_context(
                const mstch::object& object,
                const std::map<std::string,std::string>& partials);
        render_context(
                const mstch::object& object, const render_context& context);
        const mstch::node& get_node(const std::string& token);
        std::string render(const std::string& tmplt);
        template<class T, class... Args>
        void set_state(Args&&... args) {
            state = std::unique_ptr<state::render_state>(
                    new T(std::forward<Args>(args)...));
        }
    };
}

#endif //_MSTCH_RENDER_CONTEXT_H_
