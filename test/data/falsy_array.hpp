const auto falsy_array_data = mstch::map_wrapper{
        {{"list",
          mstch::array_wrapper{
                  {mstch::array_wrapper{{std::string{""}, std::string{"emptyString"}}},
                   mstch::array_wrapper{{mstch::array_wrapper{}, std::string{"emptyArray"}}},
                   mstch::array_wrapper{{0, std::string{"zero"}}},
                   mstch::array_wrapper{{mstch::node{}, std::string{"null"}}}}}}}};
