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
    public:
        class push {
        public:
            push(render_context& context, const mstch::object& obj = {});
            ~push();
            std::string render(const std::vector<token>& tokens);
        private:
            render_context& context;
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
    private:
        enum class parse_state {
            start, in_del_start, in_del, in_content, in_esccontent, in_del_end
        };
        static const mstch::node null_node;
        const mstch::node& find_node(
                const std::string& token,
                const std::deque<object>& current_objects);
        void tokenize(const std::string& tmplt, std::vector<token>& tokens);
        void strip_whitespace(std::vector<token>& tokens);
        std::string render(const std::vector<token>& tokens);
        std::map<std::string,std::string> partials;
        std::deque<mstch::object> objects;
        std::stack<std::unique_ptr<state::render_state>> state;
        std::string delim_start;
        std::string delim_end;
    };
}

#endif //_MSTCH_RENDER_CONTEXT_H_
