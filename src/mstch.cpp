#include <iostream>

#include "mstch/mstch.hpp"
#include "render_context.hpp"

using namespace mstch;

std::function<std::string(const std::string&)> mstch::config::escape;

std::string mstch::render(
    const std::string& tmplt,
    const node& root,
    const std::map<std::string,std::string>& partials)
{
  return render(tmplt, root, [&partials](const std::string& partial_name) {
    return partials.count(partial_name) ?
        boost::make_optional(partials.at(partial_name))
	  :
        boost::optional<std::string>()
      ;
  });
}

std::string mstch::render(
    const std::string& tmplt,
    const node& root,
	std::function<boost::optional<std::string>(const std::string&)> partial_loader)
{
  return render_context(root, partial_loader).render(tmplt);
}
