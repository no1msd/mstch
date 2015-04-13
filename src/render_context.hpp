#ifndef _MSTCH_RENDER_CONTEXT_H_
#define _MSTCH_RENDER_CONTEXT_H_

#include <deque>
#include <sstream>
#include <string>
#include <stack>

#include "mstch/mstch.hpp"
#include "state/render_state.hpp"

namespace mstch {
    class render_context {
    private:
        static const mstch::node null_node;
        const mstch::node& find_node(
                const std::string& token,
                const std::deque<object>& current_objects);
        std::map<std::string,std::string> partials;
        std::deque<mstch::object> objects;
        std::stack<std::unique_ptr<state::render_state>> state;
        template<class T, class... Args>
        void push_state(Args&&... args) {
            state.push(std::unique_ptr<state::render_state>(
                    new T(std::forward<Args>(args)...)));
        }
    public:
        class push {
        private:
            render_context& context;
        public:
            push(render_context& context, const mstch::object& obj = {});
            ~push();
            std::string render(const std::string& tmplt);
        };
        render_context(
                const mstch::object& object,
                const std::map<std::string,std::string>& partials);
        const mstch::node& get_node(const std::string& token);
        std::string render(const std::string& tmplt);
        std::string render_partial(const std::string& partial_name);
        template<class T, class... Args>
        void set_state(Args&&... args) {
            state.top() = std::unique_ptr<state::render_state>(
                    new T(std::forward<Args>(args)...));
        }
    };


}

#endif //_MSTCH_RENDER_CONTEXT_H_
