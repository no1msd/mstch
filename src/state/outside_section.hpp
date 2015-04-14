#ifndef _MSTCH_OUTSIDE_SECTION_H_
#define _MSTCH_OUTSIDE_SECTION_H_

#include "render_state.hpp"

namespace mstch {
    namespace state {
        class outside_section: public render_state {
        public:
            std::string render(
                    render_context& context, const token& token) override;
        };
    }
}

#endif //_MSTCH_OUTSIDE_SECTION_H_
