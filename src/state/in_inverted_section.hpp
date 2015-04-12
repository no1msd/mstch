#ifndef _MSTCH_IN_INVERTED_SECTION_H_
#define _MSTCH_IN_INVERTED_SECTION_H_

#include <sstream>
#include "render_state.hpp"

namespace mstch {
    namespace state {
        class in_inverted_section: public render_state {
        private:
            const std::string section_name;
            std::ostringstream section_text;
            int skipped_openings;
        public:
            in_inverted_section(const std::string &section_name);
            std::string render(
                    render_context &context,
                    const token &token) override;
        };
    }
}

#endif //_MSTCH_IN_INVERTED_SECTION_H_
