#include "mstch/mstch.hpp"

const auto empty_string_data =
        mstch::map_wrapper{{{"description", std::string{"That is all!"}},
                            {"child", mstch::map_wrapper{{{"description", std::string{""}}}}}}};
