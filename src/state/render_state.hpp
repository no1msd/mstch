#ifndef _MSTCH_RENDER_STATE_H_
#define _MSTCH_RENDER_STATE_H_

#include <memory>
#include "token.hpp"

namespace mstch {
    class render_context;
    namespace state {
        class render_state {
        public:
            virtual ~render_state() {}
            virtual std::string render(
                    render_context& context, const token& token) = 0;
        };
    }
}

#endif //_MSTCH_RENDER_STATE_H_
