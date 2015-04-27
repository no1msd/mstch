#pragma once

#include <sstream>
#include <vector>

#include "render_state.hpp"
#include "template_type.hpp"

namespace mstch {

class in_section: public render_state {
 public:
  enum class type { inverted, normal };
  in_section(type type, const std::string &section_name);
  std::string render(render_context &context, const token &token) override;

 private:
  const type m_type;
  const std::string section_name;
  template_type section;
  int skipped_openings;
};

}
