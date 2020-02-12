#pragma once

#include <string>
#include <variant>

namespace mstch {

using citer  = std::string::const_iterator;
using criter = std::string::const_reverse_iterator;

citer first_not_ws(citer begin, citer end);
citer first_not_ws(criter begin, criter end);
std::string html_escape(const std::string& str);
criter reverse(citer it);

template<class... Args>
auto visit(Args&&... args) -> decltype(std::visit(std::forward<Args>(args)...)) {
    return std::visit(std::forward<Args>(args)...);
}

}  // namespace mstch
