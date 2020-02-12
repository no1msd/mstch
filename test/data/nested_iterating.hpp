const mstch::node nested_iterating_data = mstch::map_wrapper{
        {{"inner",
          mstch::array_wrapper{
                  {mstch::map_wrapper{{{"foo", std::string{"foo"}},
                                       {"inner",
                                        mstch::array_wrapper{{mstch::map_wrapper{
                                                {{"bar", std::string{"bar"}}}}}}}}}}}}}};
