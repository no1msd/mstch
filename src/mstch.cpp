#include <iostream>

#include "mstch/mstch.hpp"
#include "render_context.hpp"
#include "utils.hpp"

using namespace mstch;

std::string mstch::render(
        const std::string& tmplt,
        const object& root,
        const std::map<std::string,std::string>& partials)
{
    return render_context(root, partials).render(tmplt);
}
