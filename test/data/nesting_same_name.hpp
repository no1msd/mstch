const mstch::node nesting_same_name_data = mstch::map_wrapper{
        {{"items",
          mstch::array_wrapper{
                  {mstch::map_wrapper{{{"name", std::string{"name"}},
                                       {"items", mstch::array_wrapper{{1, 2, 3, 4}}}}}}}}}};
