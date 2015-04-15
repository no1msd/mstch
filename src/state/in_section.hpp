#pragma once

#include "render_state.hpp"
#include <sstream>
#include <vector>

namespace mstch {
    namespace state {
        class in_section: public render_state {
        public:
            in_section(const std::string& section_name);
            std::string render(
                    render_context& context, const token& token) override;
        private:
            const std::string section_name;
            std::vector<token> section_tokens;
            int skipped_openings;
        };
    }
}
