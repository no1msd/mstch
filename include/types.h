#ifndef _MSTCH_TYPES_H_
#define _MSTCH_TYPES_H_

#include <vector>
#include <map>
#include <string>

#include <boost/variant.hpp>

namespace mstch {
    using node = boost::make_recursive_variant<
            boost::blank, std::string, int, bool,
            std::map<const std::string,boost::recursive_variant_>,
            std::vector<boost::recursive_variant_>>::type;
    using object = std::map<const std::string,node>;
    using array = std::vector<node>;
}

#endif //_MSTCH_TYPES_H_
