#pragma once

#include <sstream>
#include "render_state.hpp"
#include <vector>
#include "template_type.hpp"

namespace mstch {
    namespace state {
        class in_inverted_section: public render_state {
        public:
            in_inverted_section(const std::string& section_name);
            std::string render(
                    render_context& context, const token& token) override;
        private:
            const std::string section_name;
            template_type section;
            int skipped_openings;
        };
    }
}
