const mstch::node unescaped_data =
        mstch::map_wrapper{{{"title", mstch::lambda_wrapper{{[]() -> mstch::node {
                                 return std::string{"Bear > Shark"};
                             }}}}}};
