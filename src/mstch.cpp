#include <iostream>

#include "mstch/mstch.hpp"
#include "render_context.hpp"
#include "utils.hpp"

using namespace mstch;

std::string mstch::render(
    const std::string& tmplt,
    const node& root,
    const std::map<std::string,std::string>& partials)
{
  std::map<std::string, template_type> partial_templts;
  for (auto& partial: partials)
    partial_templts.insert({partial.first, {partial.second}});
  return render_context(root, partial_templts).render(tmplt);
}
