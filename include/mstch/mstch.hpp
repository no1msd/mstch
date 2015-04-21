#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

#include <boost/variant.hpp>

namespace mstch {
    namespace internal {
        template<class N>
        class object_t {
        public:
            const N& at(const std::string& name) const {
                cache[name] = (methods.at(name))();
                return cache[name];
            }

            bool has(const std::string name) const {
                return methods.count(name);
            }
        protected:
            template<class S>
            void register_methods(S* sub, std::map<std::string,N(S::*)()> methods) {
                for(auto& item: methods)
                    this->methods.insert({item.first, std::bind(item.second, sub)});
            }
        private:
            std::map<std::string, std::function<N()>> methods;
            mutable std::map<std::string, N> cache;
        };
    }

    using node = boost::make_recursive_variant<
            boost::blank, std::string, int, bool,
            std::shared_ptr<internal::object_t<boost::recursive_variant_>>,
            std::map<const std::string,boost::recursive_variant_>,
            std::vector<boost::recursive_variant_>>::type;
    using object = internal::object_t<node>;
    using map = std::map<const std::string,node>;
    using array = std::vector<node>;

    std::string render(
            const std::string& tmplt,
            const node& root,
            const std::map<std::string,std::string>& partials =
                    std::map<std::string,std::string>());
}
