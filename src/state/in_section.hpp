#ifndef _MSTCH_IN_SECTION_H_
#define _MSTCH_IN_SECTION_H_

#include "render_state.hpp"
#include <sstream>

namespace mstch {
    namespace state {
        class in_section: public render_state {
        private:
            const std::string section_name;
            std::ostringstream section_text;
            int skipped_openings;
        public:
            in_section(const std::string& section_name);
            std::string render(
                    render_context& context,
                    const token& token) override;
        };
    }
}

#endif //_MSTCH_IN_SECTION_H_
