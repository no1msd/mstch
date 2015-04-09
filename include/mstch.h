#ifndef _MSTCH_H_
#define _MSTCH_H_

#include "types.h"

namespace mstch {
    std::string render(
            const std::string& tmplt,
            const object& context,
            const std::map<std::string,std::string>& partials = std::map<std::string,std::string>());
}

#endif // _MSTCH_H_
