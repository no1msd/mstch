#pragma once

#include <string>

namespace mstch {
    using citer = std::string::const_iterator;
    using criter = std::string::const_reverse_iterator;
    citer first_not_ws(citer begin, citer end);
    citer first_not_ws(criter begin, criter end);
    std::string html_escape(std::string str);
}
