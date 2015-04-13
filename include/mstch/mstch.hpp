#ifndef _MSTCH_H_
#define _MSTCH_H_

#include <vector>
#include <map>
#include <string>
#include <functional>

#include <boost/variant.hpp>

namespace mstch {
    // booleans must be wrapped, because std::function is implicitly convertible
    // to a bool.
    class boolean {
    private:
        const bool state;
    public:
        boolean(bool b): state(b) {}
        operator bool() const { return state; }
    };

    using renderer = std::function<std::string(const std::string&)>;
    using string_lambda = std::function<std::string()>;
    using renderer_lambda = std::function<
            std::function<std::string(const std::string&,renderer)>()>;
    using node = boost::make_recursive_variant<
            boost::blank, std::string, int, boolean,
            string_lambda, renderer_lambda,
            std::map<const std::string,boost::recursive_variant_>,
            std::vector<boost::recursive_variant_>>::type;
    using object = std::map<const std::string,node>;
    using array = std::vector<node>;

    std::string render(
            const std::string& tmplt,
            const object& root,
            const std::map<std::string,std::string>& partials =
                    std::map<std::string,std::string>());
}

#endif // _MSTCH_H_
