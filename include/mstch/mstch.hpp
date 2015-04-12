#ifndef _MSTCH_H_
#define _MSTCH_H_

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

    std::string render(
            const std::string& tmplt,
            const object& context,
            const std::map<std::string,std::string>& partials =
                    std::map<std::string,std::string>());
}

#endif // _MSTCH_H_
