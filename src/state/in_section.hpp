#pragma once

#include "render_state.hpp"
#include <sstream>
#include <vector>
#include "template_type.hpp"

namespace mstch {
    namespace state {
        class in_section: public render_state {
        public:
            in_section(const std::string& section_name);
            std::string render(
                    render_context& context, const token& token) override;
        private:
            const std::string section_name;
            template_type section;
            int skipped_openings;
        };
    }
}
